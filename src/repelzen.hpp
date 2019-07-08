#include <rack.hpp>

using namespace rack;
extern Plugin *pluginInstance;

/* the original modulo does not deal with negative numbers correctly
   For example -1%12 should be 11, but it is -1*/
inline int modN(int k, int n) {
    return ((k %= n) < 0) ? k+n : k;
}

/* modified version of ceil that works with negative values (example: -2.3 becomes -3) */
inline int ceilN(float x) {
    return (x < 0) ? (int)floor(x) : (int)ceil(x);
}

////////// fast math //////////

template <typename T>
static T tanh_pade(T x) {
	// Padé approximant of tanh
	x = simd::clamp(x, -5.f, 5.f);
    return (T(x * (135135 + simd::pow(x, 2) * (17325 + simd::pow(x, 2) * (378 + simd::pow(x, 2))))))
         / (T(135135 + simd::pow(x, 2) * (62370 + simd::pow(x, 2) * (3150 + 28 * simd::pow(x, 2)))));
}

////////// custom components for repelzen redesign //////////

struct ReButtonL : app::SvgSwitch {
	ReButtonL() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/button_l.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/button_l_push.svg")));
	}
};

struct ReButtonM : app::SvgSwitch {
	ReButtonM() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/button_m.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/button_m_push.svg")));
	}
};

struct ReIOPort : app::SvgPort {
    ReIOPort() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/jack.svg")));
    }
};

/* knobs */
struct ReKnobLGrey : app::SvgKnob {
    ReKnobLGrey() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/knob_l_grey.svg")));
    }
};

struct ReKnobMBlue : app::SvgKnob {
    ReKnobMBlue() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/knob_m_blue.svg")));
    }
};

struct ReKnobMGreen : app::SvgKnob {
    ReKnobMGreen() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/knob_m_green.svg")));
    }
};

struct ReKnobMGrey : app::SvgKnob {
    ReKnobMGrey() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/knob_m_grey.svg")));
    }
};

struct ReKnobMRed : app::SvgKnob {
    ReKnobMRed() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/knob_m_red.svg")));
    }
};

struct ReKnobMYellow : app::SvgKnob {
    ReKnobMYellow() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/knob_m_yellow.svg")));
    }
};

struct ReKnobSBlue : app::SvgKnob {
    ReKnobSBlue() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/knob_s_blue.svg")));
    }
};

struct ReKnobSGreen : app::SvgKnob {
    ReKnobSGreen() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/knob_s_green.svg")));
    }
};

struct ReKnobSGrey : app::SvgKnob {
    ReKnobSGrey() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/knob_s_grey.svg")));
    }
};

struct ReKnobSRed : app::SvgKnob {
    ReKnobSRed() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/knob_s_red.svg")));
    }
};

struct ReKnobSYellow : app::SvgKnob {
    ReKnobSYellow() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/knob_s_yellow.svg")));
    }
};

/* snap knobs */
struct ReSnapKnobLGrey : ReKnobLGrey {
    ReSnapKnobLGrey() {
        snap = true;
    }
};

struct ReSnapKnobBlue : ReKnobMBlue {
    ReSnapKnobBlue() {
        snap = true;
    }
};

struct ReSnapKnobGreen : ReKnobMGreen {
    ReSnapKnobGreen() {
        snap = true;
    }
};

struct ReSnapKnobSBlue : ReKnobSBlue {
    ReSnapKnobSBlue() {
        snap = true;
    }
};

struct ReSnapKnobSGreen : ReKnobSGreen {
    ReSnapKnobSGreen() {
        snap = true;
    }
};

struct ReSnapKnobSRed : ReKnobSRed {
    ReSnapKnobSRed() {
        snap = true;
    }
};

struct ReSnapKnobSYellow : ReKnobSYellow {
    ReSnapKnobSYellow() {
        snap = true;
    }
};

/* switches */
struct ReSwitch2 : app::SvgSwitch {
    ReSwitch2() {
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/switch2_1.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/switch2_2.svg")));
    }
};

struct ReSwitch3 : app::SvgSwitch {
    ReSwitch3() {
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/switch3_1.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/switch3_2.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/recomp/switch3_3.svg")));
    }
};

/* lights */
template <typename BASE>
struct ReLightM : BASE { // to go with ReButtonM as bezel
    ReLightM() {
        this->box.size = (Vec(17, 17));
    }
};

struct ReRedLight : app::ModuleLightWidget {
    ReRedLight() {
        bgColor = nvgRGB(0x5a, 0x5a, 0x5a);
        borderColor = nvgRGBA(0, 0, 0, 0x60);
        addBaseColor(nvgRGB(0xff, 0x25, 0x4a));
    }
};

struct ReBlueLight : app::ModuleLightWidget {
    ReBlueLight() {
        bgColor = nvgRGB(0x5a, 0x5a, 0x5a);
        borderColor = nvgRGBA(0, 0, 0, 0x60);
        addBaseColor(nvgRGB(0x25, 0xc0, 0xff));
    }
};




// extern Model *modelQuadSeq;
// extern Model *modelGateSeq;
// extern Model *modelDice;
// extern Model *modelWalker;
extern Model *modelBurst;
extern Model *modelFolder;
extern Model *modelErwin;
extern Model *modelWerner;
extern Model *modelMixer;
