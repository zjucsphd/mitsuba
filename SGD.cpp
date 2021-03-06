#include <mitsuba/render/bsdf.h>
#include <mitsuba/hw/basicshader.h>
#include <mitsuba/core/warp.h>

MTS_NAMESPACE_BEGIN

class SGD : public BSDF {
public:
	SGD(const Properties &props)
		: BSDF(props) { 
	    m_diffuseReflectance = props.getSpectrum("diffuseReflectance", Spectrum(0.5f));
	    m_specularReflectance = props.getSpectrum("specularReflectance", Spectrum(0.2f));
	    m_alpha = props.getSpectrum("alpha", Spectrum(0.1f));
	    m_p = props.getSpectrum("p", Spectrum(0.1f));
	    m_Kap = props.getSpectrum("m_Kappa", Spectrum(0.1f));
	    m_F0 = props.getSpectrum("F0", Spectrum(0.1f));
	    m_F1 = props.getSpectrum("F1", Spectrum(0.1f));
	    m_lambda = props.getSpectrum("lambda", Spectrum(0.1f));
	    m_c = props.getSpectrum("c", Spectrum(0.1f));
	    m_k = props.getSpectrum("k", Spectrum(0.1f));
	    m_theta0 = props.getSpectrum("theta0", Spectrum(0.1f));
	    m_roughness = props.getFloat("roughness", 0.1f);
	    
	}

	SGD(Stream *stream, InstanceManager *manager)
		: BSDF(stream, manager) {
	    m_diffuseReflectance = Spectrum(stream);
	    m_specularReflectance = Spectrum(stream);
	    m_alpha = Spectrum(stream);
	    m_p = Spectrum(stream);
	    m_Kap = Spectrum(stream);
	    m_F0 = Spectrum(stream);
	    m_F1 = Spectrum(stream);
	    m_lambda = Spectrum(stream);
	    m_c = Spectrum(stream);
	    m_k = Spectrum(stream);
	    m_theta0 = Spectrum(stream);
	    m_roughness = stream->readFloat();

	    configure();
	}

	void configure() {
		m_components.clear();
		m_components.push_back(EGlossyReflection | EFrontSide );
		m_components.push_back(EDiffuseReflection | EFrontSide );
		m_usesRayDifferentials = false;

		Float dAvg = m_diffuseReflectance.getLuminance(),
		      sAvg = m_specularReflectance.getLuminance();
		m_specularSamplingWeight = sAvg / (dAvg + sAvg);

		BSDF::configure();
	}

	Spectrum eval(const BSDFSamplingRecord &bRec, EMeasure measure) const {
	        /* sanity check */
	        if(measure != ESolidAngle || 
		   Frame::cosTheta(bRec.wi) <= 0 ||
	           Frame::cosTheta(bRec.wo) <= 0)
		  return Spectrum(0.0f);

  	        /* which components to eval */
		bool hasSpecular = (bRec.typeMask & EGlossyReflection)
				&& (bRec.component == -1 || bRec.component == 0);
		bool hasDiffuse  = (bRec.typeMask & EDiffuseReflection)
				&& (bRec.component == -1 || bRec.component == 1);

		/* eval spec */
		Spectrum result(0.0f);
		if (hasSpecular) {
		    Vector H = normalize(bRec.wo+bRec.wi);
		    const Float cosThetaH = Frame::cosTheta(H);
			if(cosThetaH > 0.0f)
			{
			  // evaluate NDF
			  //const Float roughness2 = m_roughness*m_roughness;
			  const Float cosTheta2 = Frame::cosTheta2(H);
			  const Float Hwi = dot(bRec.wi, H);
			  //const Float Hwo = dot(bRec.wo, H);
			  const Float tanTheta2 = Frame::tanTheta2(H);

			  Float P22thetaM[3];
			  for (int idx=0; idx <3; ++idx)
			  {
			  	P22thetaM[idx] = m_Kap[idx] * (math::fastexp(-(m_alpha[idx]+tanTheta2/m_alpha[idx]))) / (std::pow(m_alpha[idx]+tanTheta2/m_alpha[idx], m_p[idx]));
			  }

			  const Spectrum P22 = Spectrum(P22thetaM);

			  Float Chi;
			  if (cosThetaH > 0.0f)
			  	Chi = 1.0f;
			  else
			  	Chi = 0.0f;
			  const Spectrum D = Chi*P22*INV_PI/(cosTheta2*cosTheta2);

			  // compute shadowing and masking
			  const Float cosThetai = Frame::cosTheta(bRec.wo);
			  const Float cosThetao = Frame::cosTheta(bRec.wi);
			  // compute G(i,o) = G1(i)*G1(o)
			  Float Gio[3];
			  for (int idx=0; idx<3; ++idx)
			  {
			  	Gio[idx] = G1(idx, cosThetai)*G1(idx, cosThetao);
			  }
			  const Spectrum G = Spectrum(Gio);

			  // compute Fresnel
			  Float fThetaD[3];
			  for (int idx=0; idx<3; ++idx)
			  {
			  	fThetaD[idx] = fresnel(m_F0[idx], m_F1[idx], Hwi);
			  }
			  const Spectrum F = Spectrum(fThetaD);

			  // evaluate the microfacet model
			  result += m_specularReflectance * INV_PI * D * G * F / Frame::cosTheta(bRec.wi);
			}
		}

		/* eval diffuse */
		if (hasDiffuse)
		  result += m_diffuseReflectance * INV_PI * Frame::cosTheta(bRec.wo);

		// Done.
		return result;
	        }

	Float pdf(const BSDFSamplingRecord &bRec, EMeasure measure) const {
	        if (measure != ESolidAngle ||
			Frame::cosTheta(bRec.wi) <= 0 ||
			Frame::cosTheta(bRec.wo) <= 0 ||
			((bRec.component != -1 && bRec.component != 0) ||
			!(bRec.typeMask & EGlossyReflection)))
			return 0.0f;

		bool hasSpecular = (bRec.typeMask & EGlossyReflection)
				&& (bRec.component == -1 || bRec.component == 0);
		bool hasDiffuse  = (bRec.typeMask & EDiffuseReflection)
				&& (bRec.component == -1 || bRec.component == 1);

		Float diffuseProb = 0.0f, specProb = 0.0f;

		//* diffuse pdf */
		if (hasDiffuse)
			diffuseProb = warp::squareToCosineHemispherePdf(bRec.wo);

		/* specular pdf */
		if (hasSpecular) {
			Vector H = bRec.wo+bRec.wi;   Float Hlen = H.length();
			if(Hlen == 0.0f) specProb = 0.0f;
			else
			{
			  H /= Hlen;
			  const Float roughness2 = m_roughness*m_roughness;
			  const Float cosTheta2 = Frame::cosTheta2(H);
			  specProb = INV_PI * Frame::cosTheta(H) * math::fastexp(-Frame::tanTheta2(H)/roughness2) / (roughness2 * cosTheta2*cosTheta2) / (4.0f * absDot(bRec.wo, H));
			}
		}

		if (hasDiffuse && hasSpecular)
			return m_specularSamplingWeight * specProb + (1.0f-m_specularSamplingWeight) * diffuseProb;
		else if (hasDiffuse)
			return diffuseProb;
		else if (hasSpecular)
			return specProb;
		else
			return 0.0f;
	}

	Spectrum sample(BSDFSamplingRecord &bRec, Float &pdf, const Point2 &_sample) const {
	        Point2 sample(_sample);


		bool hasSpecular = (bRec.typeMask & EGlossyReflection)
				&& (bRec.component == -1 || bRec.component == 0);
		bool hasDiffuse  = (bRec.typeMask & EDiffuseReflection)
				&& (bRec.component == -1 || bRec.component == 1);


		if (!hasSpecular && !hasDiffuse)
			return Spectrum(0.0f);


		// determine which component to sample
		bool choseSpecular = hasSpecular;
		if (hasDiffuse && hasSpecular) {
			if (sample.x <= m_specularSamplingWeight) {
				sample.x /= m_specularSamplingWeight;
			} else {
				sample.x = (sample.x - m_specularSamplingWeight)
					/ (1.0f-m_specularSamplingWeight);
				choseSpecular = false;
			}
		}


		/* sample specular */
		if (choseSpecular) {
			Float cosThetaM = 0.0f, phiM = (2.0f * M_PI) * sample.y;
			Float tanThetaMSqr = -m_roughness*m_roughness * math::fastlog(1.0f - sample.x);
			cosThetaM = 1.0f / std::sqrt(1.0f + tanThetaMSqr);
			const Float sinThetaM = std::sqrt(std::max((Float) 0.0f, 1.0f - cosThetaM*cosThetaM));
			Float sinPhiM, cosPhiM;
			math::sincos(phiM, &sinPhiM, &cosPhiM);

			const Normal m = Vector(sinThetaM * cosPhiM,sinThetaM * sinPhiM,cosThetaM);

			// Perfect specular reflection based on the microsurface normal
			bRec.wo = 2.0f * dot(bRec.wi, m) * Vector(m) - bRec.wi;
			bRec.sampledComponent = 0;
			bRec.sampledType = EGlossyReflection;

	        /* sample diffuse */
		} else {
	   	        bRec.wo = warp::squareToCosineHemisphere(sample);
			bRec.sampledComponent = 1;
			bRec.sampledType = EDiffuseReflection;
		}
		bRec.eta = 1.0f;

		pdf = SGD::pdf(bRec, ESolidAngle);

		/* unoptimized evaluation, explicit division of evaluation / pdf. */
		if (pdf == 0 || Frame::cosTheta(bRec.wo) <= 0)
			return Spectrum(0.0f);
		else
			return eval(bRec, ESolidAngle) / pdf;
	}

	Spectrum sample(BSDFSamplingRecord &bRec, const Point2 &sample) const {
    	        Float pdf;
		return SGD::sample(bRec, pdf, sample);
	}

	void serialize(Stream *stream, InstanceManager *manager) const {
		BSDF::serialize(stream, manager);

		m_diffuseReflectance.serialize(stream);
		m_specularReflectance.serialize(stream);
		m_alpha.serialize(stream);
		m_p.serialize(stream);
		m_Kap.serialize(stream);
		m_F0.serialize(stream);
		m_F1.serialize(stream);
		m_lambda.serialize(stream);
		m_c.serialize(stream);
		m_k.serialize(stream);
		m_theta0.serialize(stream);
		stream->writeFloat( m_roughness );
	}

	Float getRoughness(const Intersection &its, int component) const {
	       return m_roughness;
	}

	std::string toString() const {
	       std::ostringstream oss;
 	       oss << "SGD[" << endl
	           << " id = \"" << getID() << "\"," << endl
		   << " diffuseReflectance = " << indent(m_diffuseReflectance.toString()) << ", " << endl
		   << " specularReflectance = " << indent(m_specularReflectance.toString()) << ", " << endl
		   << "]";
	       return oss.str();
	}

	Shader *createShader(Renderer *renderer) const;

	MTS_DECLARE_CLASS()
private:
	// helper method
	inline Float fresnel(const Float& F0, const Float& F1, const Float& c) const
    {
	  return F0 + (1.0f - F0)*pow(1.0-c, 5.0f) - F1*c;
	}

	inline Float G1(const int idx, const Float& cosTheta) const
    {
    	Float theta = acos(cosTheta);
    	Float theta0 = m_theta0[idx];
    	Float lambda = m_lambda[idx];
    	Float c = m_c[idx];
    	Float k = m_k[idx];
    	if (theta > theta0)
    		return 1.0f + lambda*(1.0f-math::fastexp(c*std::pow(theta-theta0, k)));
    	else
    		return 1.0f;
	}

	// attribtues
    Spectrum m_F0;
    Spectrum m_F1;
    Spectrum m_alpha;
    Spectrum m_p;
    Spectrum m_Kap;
    Spectrum m_lambda;
    Spectrum m_c;
    Spectrum m_k;
    Spectrum m_theta0;
    Float m_roughness;
    Spectrum m_diffuseReflectance;
    Spectrum m_specularReflectance;

    Float m_specularSamplingWeight;
};

// ================ Hardware shader implementation ================

/* SGD shader-- render as a 'black box' */
class SGDShader : public Shader {
public:
	SGDShader(Renderer *renderer) :
		Shader(renderer, EBSDFShader) {
		m_flags = ETransparent;
	}

	void generateCode(std::ostringstream &oss,
			const std::string &evalName,
			const std::vector<std::string> &depNames) const {
		oss << "vec3 " << evalName << "(vec2 uv, vec3 wi, vec3 wo) {" << endl
			<< "    return vec3(0.0);" << endl
			<< "}" << endl;
		oss << "vec3 " << evalName << "_diffuse(vec2 uv, vec3 wi, vec3 wo) {" << endl
			<< "    return vec3(0.0);" << endl
			<< "}" << endl;
	}
	MTS_DECLARE_CLASS()
};

Shader *SGD::createShader(Renderer *renderer) const {
	return new SGDShader(renderer);
}

MTS_IMPLEMENT_CLASS(SGDShader, false, Shader)
MTS_IMPLEMENT_CLASS_S(SGD, false, BSDF)
MTS_EXPORT_PLUGIN(SGD, "SGD BSDF");
MTS_NAMESPACE_END
