#include "rtcstreamingtracker.h"

RTCStreamingTracker::RTCStreamingTracker()
{

}
class RTCStreamingTracker {
  get isConfigured() {
    return void 0 !== this.instance;
  }
  configure(e) {
    var n = this;
    return _asyncToGenerator$i(function* () {
      n.instance = e.instance;
    })();
  }
  handleEvent(e, n, d) {}
  loadScript() {
    return _asyncToGenerator$i(function* () {
      if (!bs.urls.rtc) throw new Error("bag.urls.rtc is not configured");
      yield loadScript(bs.urls.rtc);
    })();
  }
  prepareReportingAgent(e) {
    this.clearReportingAgent();
    const {Sender: n, ClientName: d, ServiceName: h, ApplicationName: p, ReportingStoreBag: y, DeviceName: m} = window.rtc.RTCReportingAgentConfigKeys;
    e = null != e ? e : this.instance.nowPlayingItem;
    const g = function (e) {
      for (var n = 1; n < arguments.length; n++) {
        var d = null != arguments[n] ? arguments[n] : {}, h = Object.keys(d);
        "function" == typeof Object.getOwnPropertySymbols && (h = h.concat(Object.getOwnPropertySymbols(d).filter(function (e) {
          return Object.getOwnPropertyDescriptor(d, e).enumerable;
        }))), h.forEach(function (n) {
          n in e ? Object.defineProperty(e, n, {value: d[n], enumerable: true, configurable: true, writable: true}) : e[n] = d[n], e;
        });
      }
      return e;
    }({firmwareVersion: this.generateBrowserVersion(), model: this.options.browserName}, this.getMediaIdentifiers(e));
    void 0 === this._storeBag && (this._storeBag = this.generateStoreBag());
    const b = {[n]: "HLSJS", [d]: this.options.clientName, [h]: this.options.serviceName, [p]: this.options.applicationName, [y]: this._storeBag, [m]: this.options.osVersion, userInfoDict: g};
    return So.debug("RTC: creating reporting agent with config", b), this.reportingAgent = new window.rtc.RTCReportingAgent(b), So.debug("RTC: created reporting agent", this.reportingAgent), this.reportingAgent;
  }
  cleanup() {
    var e = this;
    return _asyncToGenerator$i(function* () {
      e.clearReportingAgent();
    })();
  }
  getMediaIdentifiers(e) {
    const n = null == e ? void 0 : e.defaultPlayable;
    if (n) {
      var d;
      const e = {};
      return void 0 !== (null === (d = n.mediaMetrics) || void 0 === d ? void 0 : d.MediaIdentifier) && (e.MediaIdentifier = n.mediaMetrics.MediaIdentifier), void 0 !== n.channelId && (e.ContentProvider = n.channelId), e;
    }
    return "musicVideo" === (null == e ? void 0 : e.type) ? {MediaIdentifier: "adamid=" + e.id} : (null == e ? void 0 : e.isLiveVideoStation) ? {MediaIdentifier: "raid=" + e.id} : void 0;
  }
  clearReportingAgent() {
    void 0 !== this.reportingAgent && (this.reportingAgent.destroy(), So.debug("RTC: called destroy on reporting agent", this.reportingAgent), this.reportingAgent = void 0);
  }
  generateBrowserVersion() {
    return this.options.browserMajorVersion ? `${this.options.browserMajorVersion}.${this.options.browserMinorVersion || 0}` : "unknown";
  }
  generateStoreBag() {
    var e;
    const {storeBagURL: n, clientName: d, applicationName: h, serviceName: p, browserName: y} = this.options, m = {iTunesAppVersion: `${`${bs.app.name}-${bs.app.build}`}/${null === (e = this.instance) || void 0 === e ? void 0 : e.version}`}, g = new window.rtc.RTCStorebag.RTCReportingStoreBag(n, d, p, h, y, m);
    return So.debug("RTC: created store bag", g), g;
  }
  constructor(e) {
    this.requestedEvents = [], this.options = e;
  }
}
