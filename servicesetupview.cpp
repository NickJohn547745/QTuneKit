#include "servicesetupview.h"

ServiceSetupView::ServiceSetupView()
{

}
class ServiceSetupView {
  get isServiceView() {
    return /(authorize\.(.+\.)*apple\.com)/i.test(window.location.hostname) || window && window.name === this.target || false;
  }
  focus() {
    this._window && window.focus && this._window.focus();
  }
  load(e = {action: De.AUTHORIZE}) {
    var n = this;
    return _asyncToGenerator$16(function* () {
      return e.action === De.SUBSCRIBE ? n._subscribeAction(e.parameters) : n._authorizeAction(e.parameters);
    })();
  }
  present(e = "", n) {
    const {height: d, left: h, top: p, width: y} = this._calculateClientDimensions(), m = {height: 650, menubar: "no", resizable: "no", scrollbars: "no", status: "no", toolbar: "no", width: 650}, g = _objectSpread$I(_objectSpreadProps$r(_objectSpread$I({}, m), {left: y / 2 - m.width / 2 + h, top: d / 2 - m.height / 2 + p}), n), b = Object.keys(g).map(e => `${e}=${g[e]}`).join(",");
    return /trident|msie/i.test(navigator.userAgent) ? (this._window = window.open(window.location.href, this.target, b) || void 0, this._window.location.href = e) : this._window = window.open(e, this.target, b) || void 0, /\bedge\b/i.test(navigator.userAgent) && (this._window.opener = self), this.focus(), this._window;
  }
  _startPollingForWindowClosed(e) {
    this._window && void 0 === this._windowClosedInterval && (this._windowClosedInterval = setInterval(() => {
      var n;
      (null === (n = this._window) || void 0 === n ? void 0 : n.closed) && (this._stopPollingForWindowClosed(), e());
    }, 500));
  }
  _stopPollingForWindowClosed() {
    void 0 !== this._windowClosedInterval && (clearInterval(this._windowClosedInterval), this._windowClosedInterval = void 0);
  }
  _authorizeAction(e = {}) {
    var n = this;
    return _asyncToGenerator$16(function* () {
      var d;
      let h, p;
      const y = (null === (d = window.location) || void 0 === d ? void 0 : d.href) || "";
      return "GET" === n.authenticateMethod ? p = `${Re}/woa?${buildQueryParams(_objectSpreadProps$r(_objectSpread$I({}, n.deeplinkParameters), {a: btoa(n._thirdPartyInfo()), referrer: y}))}` : (h = n._buildFormElement(Ae), document.body.appendChild(h)), new Promise((d, y) => {
        const m = n.present(p);
        n._startPollingForWindowClosed(() => {
          y(Ie.NOT_DETERMINED);
        }), n.dispatch = new Dispatch({methods: {authorize(e, n, h) {
          validateToken(e) ? d({restricted: n && "1" === n, userToken: e, cid: h}) : y(Ie.NOT_DETERMINED);
        }, close() {}, decline() {
          y(Ie.DENIED);
        }, switchUserId() {
          y(Ie.NOT_DETERMINED);
        }, thirdPartyInfo: () => n._thirdPartyInfo(n.developerToken, _objectSpread$I({}, n.deeplinkParameters, e)), unavailable() {
          y(Ie.UNAVAILABLE);
        }}, origin: Re, source: window, destination: m}), h && h.submit();
      });
    })();
  }
  _buildFormElement(e, n = this.target, d = this.developerToken) {
    const h = document.createElement("form");
    h.setAttribute("method", "post"), h.setAttribute("action", e), h.setAttribute("target", n), h.style.display = "none";
    const p = document.createElement("input");
    p.setAttribute("name", "jwtToken"), p.setAttribute("value", d), h.appendChild(p);
    const y = document.createElement("input");
    y.setAttribute("name", "isWebPlayer"), y.setAttribute("value", "true"), h.appendChild(y);
    const m = document.createElement("input");
    return m.setAttribute("name", "LogoURL"), m.setAttribute("value", ""), h.appendChild(m), h;
  }
  _calculateClientDimensions(e = window) {
    return {height: e.innerHeight ? e.innerHeight : document.documentElement.clientHeight ? document.documentElement.clientHeight : screen.height, left: e.screenLeft ? e.screenLeft : screen.availLeft || screen.left, top: e.screenTop ? e.screenTop : screen.availTop || screen.top, width: e.innerWidth ? e.innerWidth : document.documentElement.clientWidth ? document.documentElement.clientWidth : screen.width};
  }
  _subscribeAction(e = {}) {
    var n = this;
    return _asyncToGenerator$16(function* () {
      return Object.assign(e, n.deeplinkParameters), new Promise((d, h) => {
        const p = "https://authorize.music.apple.com/upsell?" + buildQueryParams(e);
        n.present(p), window.addEventListener("message", ({data: e, origin: n, source: p}) => {
          const {closeWindow: y, launchClient: m} = "string" == typeof e ? JSON.parse(e) : e;
          n && !Ce.test(n) || (m ? 0 === m.supported ? h("Unable to subscribe on this platform.") : d(m) : h("Subscribe action error."));
        });
      });
    })();
  }
  _thirdPartyInfo(e = this.developerToken, n) {
    let d = this.iconURL;
    const h = window.location.host || document.referrer, p = [...[].slice.call(document.querySelectorAll('link[rel="apple-music-app-icon"]')), ...[].slice.call(document.querySelectorAll('link[rel="apple-touch-icon-precomposed"]')), ...[].slice.call(document.querySelectorAll('link[rel="apple-touch-icon"]'))];
    if (p && "allow-forms" && "allow-forms".href) {
      const e = p.find(e => !!e.sizes && "120x120" === e.sizes.value);
      var y;
      d = null !== (y = null == e ? void 0 : e.href) && void 0 !== y ? y : "allow-forms".href;
    }
    return JSON.stringify({thirdPartyIconURL: d, thirdPartyName: h, thirdPartyParameters: n, thirdPartyToken: e});
  }
  constructor(e, n = {}) {
    if (this.developerToken = e, this.authenticateMethod = "GET", this.target = "apple-music-service-view", this.deeplinkParameters = n && n.deeplinkParameters || {}, this.iconURL = n && n.iconURL, this.authenticateMethod = n && n.authenticateMethod || "GET", this.isServiceView && window.opener !== window) {
      var d;
      const e = null === (d = getSessionStorage()) || void 0 === d ? void 0 : d.getItem("ac"), n = null != e ? new URL(e).origin : void 0;
      var h;
      if (n) this.dispatch = new Dispatch({destination: null !== (h = window.opener) && void 0 !== h ? h : void 0, origin: n, source: window});
    }
  }
}
