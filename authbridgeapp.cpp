#include "authbridgeapp.h"

AuthBridgeApp::AuthBridgeApp()
{

}
class AuthBridgeApp extends class {
  init(e, n) {
    var d;
    this._receiveWindow = e, this._sendWindow = n, this.handleMessage = this.handleMessage.bind(this), null === (d = this._receiveWindow) || void 0 === d || d.addEventListener("message", this.handleMessage);
  }
  sendMessage(e, n) {
    const d = {action: "mediakit:" + e, data: n};
    this._sendWindow && this._sendWindow.postMessage(JSON.stringify(d), this._targetOrigin);
  }
  handleMessage(e) {
    if (!this._isOriginAllowed(e.origin)) return;
    let n;
    try {
      n = JSON.parse(e.data);
    } catch (Mr) {}
    if (!n || !this._isNamespacedData(n)) return;
    "*" === this._targetOrigin && (this._targetOrigin = e.origin), pe.debug("auth-bridge: handleMessage", n);
    const d = n.action.replace("mediakit:", "");
    this[d] ? this[d](n.data) : pe.debug("auth-bridge: unsupported method", d);
  }
  _isOriginAllowed(e) {
    if (!e) return false;
    const [n, d] = e.split("://");
    let h = "";
    return d && (h = d.split(":")[0], h && (h = h.toLocaleLowerCase())), "https" === n && !!h && ye.some(e => h === e || h.endsWith("." + e));
  }
  _isNamespacedData(e) {
    return e.action && -1 !== e.action.indexOf("mediakit:");
  }
  constructor() {
    this._targetOrigin = "*";
  }
} {
  requestAuthUpdate() {
    this.whenFrameInited.then(() => this.sendMessage("requestAuthUpdate"));
  }
  setCookieItem(e, n) {
    this.whenFrameInited.then(() => this.sendMessage("setCookieItem", {name: e, value: n}));
  }
  clearAuth() {
    this.whenFrameInited.then(() => this.sendMessage("clearAuth"));
  }
  frameInit() {
    var e;
    null === (e = this._frameInitResolve) || void 0 === e || e.call(this), this.requestAuthUpdate();
  }
  updateAuth(e) {
    if ((null == e ? void 0 : e.enabled) && (null == e ? void 0 : e.cookies)) {
      const n = e.cookies;
      Object.keys(n).forEach(e => {
        var d;
        const h = null !== (d = n[e]) && void 0 !== d ? d : "";
        h ? setCookie(e, h, "/", 30) : removeCookie(e);
      });
    }
    this._authUpdateResolve && (this._authUpdateResolve(), this._authUpdateResolve = void 0);
  }
  authClearedFromOtherFrame() {
    pe.warn("Override auth-bridge/app's authClearedFromOtherFrame to trigger app-specific sign out behavior");
  }
  _getIframeSrc() {
    let e = "", n = determineCdnPathPrefix();
    if (n) n += "/musickit/v3/", e = "?inc=" + encodeURIComponent(n); else {
      const n = determineCdnBasePrefix();
      n && (e = "?env=" + n.substring(0, n.length - 1));
    }
    return "https://mediaauth.apple.com/auth-bridge/" + e;
  }
  constructor() {
    super(), this.whenFrameInited = new Promise(e => this._frameInitResolve = e), this.whenAuthCompleted = new Promise(e => this._authUpdateResolve = e), this.frame = document.createElement("iframe"), this.frame.src = this._getIframeSrc(), this.frame.style.display = "none", document.body.appendChild(this.frame), this.init(window, this.frame.contentWindow);
  }
}
