#pragma once

#include "hyprland-input-capture-v1.hpp"
#include "../protocols/WaylandProtocol.hpp"
#include "../devices/IKeyboard.hpp"
#include "WaylandProtocol.hpp"
#include <hyprutils/math/Vector2D.hpp>

class CInputCaptureProtocol : public IWaylandProtocol {
  public:
    CInputCaptureProtocol(const wl_interface* iface, const int& ver, const std::string& name);
    virtual void bindManager(wl_client* client, void* data, uint32_t ver, uint32_t id);

    //
    bool isCaptured();

    void updateKeymap();
    void forceRelease();

    void sendMotion(const Vector2D& absolutePosition, const Vector2D& delta);
    void sendKey(uint32_t keyCode, hyprlandInputCaptureManagerV1KeyState state);
    void sendModifiers(uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group);
    void sendButton(uint32_t button, hyprlandInputCaptureManagerV1ButtonState state);
    void sendAxis(hyprlandInputCaptureManagerV1Axis axis, double value);
    void sendAxisValue120(hyprlandInputCaptureManagerV1Axis axis, int32_t value120);
    void sendAxisStop(hyprlandInputCaptureManagerV1Axis axis);

    void sendFrame();

  private:
    void sendKeymap(SP<IKeyboard> keyboard, const Hyprutils::Memory::CUniquePointer<CHyprlandInputCaptureManagerV1>& manager);

    bool active = false;
    //
    void         sendAbsoluteMotion(const Vector2D& absolutePosition, const Vector2D& delta);

  private:
    void onManagerResourceDestroy(wl_resource* res);
    void onCapture(CHyprlandInputCaptureManagerV1* pMgr);
    void onRelease(CHyprlandInputCaptureManagerV1* pMgr);

    std::vector<UP<CHyprlandInputCaptureManagerV1>> m_vManagers;
};

namespace PROTO {
    inline UP<CInputCaptureProtocol> inputCapture;
}
