#include "browser.h"

Browser::Browser()
{

}
class Browser {
  static supportsEs6() {
    if ("undefined" == typeof Symbol) return false;
    try {
      new Function('"use strict";class Foo {}')(), new Function('"use strict";var bar = (x) => x+1')();
    } catch (Mr) {
      return false;
    }
    return true;
  }
  constructor(e, n) {
    var d;
    e || (e = "undefined" != typeof window && (null === window || void 0 === window || null === (d = window.navigator) || void 0 === d ? void 0 : d.userAgent) ? window.navigator.userAgent : "");
    n || (n = "undefined" != typeof window && void 0 !== window.navigator ? window.navigator : void 0);
    const h = e.toLowerCase();
    this.isEdge = /\sedge\//.test(h), this.isChrome = !this.isEdge && /chrome/.test(h), this.isSafari = !this.isEdge && !this.isChrome && /safari/.test(h), this.isFirefox = !this.isEdge && !this.isChrome && !this.isSafari && /firefox/.test(h), this.isIE = !this.isEdge && !this.isChrome && !this.isSafari && !this.isFirefox && /trident|msie/.test(h), this.isMobile = /mobile/.test(h), this.isAndroid = /android/.test(h), this.isiOS = this.isMobile && /iphone|ipad|ipod/.test(h), this.isMacOs = !this.isMobile && /macintosh/.test(h), this.isiPadOs = this.isMobile && /ipad/.test(h) || this.isMacOs && void 0 !== (null == n ? void 0 : n.maxTouchPoints) && n.maxTouchPoints > 2, this.isWebView = /(webview|(iphone|ipod|ipad)(?!.*safari\/)|android.*(wv|\.0\.0\.0)|\bfb[\w_]+\/(?:messenger)?|\binstagram|\btwitter)/.test(h), this.isEdge ? this.engineVersion = h.match(/(?:edge).(\d+)/) : (this.version = h.match(/(?:chrome|version|firefox|msie|rv).(\d+)\.(\d+)/), this.engineVersion = h.match(/(?:applewebkit|gecko|trident).(\d+)/)), this.version && (this.majorVersion = parseInt(this.version[1], 10), this.minorVersion = parseInt(this.version[2], 10)), this.engineVersion && (this.engineMajorVersion = parseInt(this.engineVersion[1], 10));
  }
}
