#include "playactivitysender.h"

PlayActivitySender::PlayActivitySender()
{

}
class PlayActivitySender {
  get accessToken() {
    return invoke(this._accessToken);
  }
  get musicUserToken() {
    return invoke(this._musicUserToken);
  }
  get url() {
    return this._isQA ? "https://universal-activity-service.itunes.apple.com/qa/play" : "https://universal-activity-service.itunes.apple.com/play";
  }
  send(e) {
    var n, d = this;
    return (n = function* () {
      const n = {client_id: d._clientId, event_type: d._eventType, data: ensureArray(e).map(toTimeMeasuredData)};
      if (0 === n.data.length) throw new Error("send() called without any data");
      const h = d._generateFetchOptions({method: "POST", body: JSON.stringify(n), headers: d.headers()});
      return yield d._fetch(d.url, h), d._logInfo && console.info("play activity:", d._sourceType === Rr.AMAZON ? JSON.stringify(n) : n), n;
    }, function () {
      var e = this, d = arguments;
      return new Promise(function (h, p) {
        var y = n.apply(e, d);
        function _next(e) {
          asyncGeneratorStep$11(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$11(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  baseHeaders() {
    var e, n;
    const d = null !== (n = null === (e = this._fetchOptions) || void 0 === e ? void 0 : e.headers) && void 0 !== n ? n : {};
    return d instanceof this._headersClass ? new this._headersClass(Array.from(d.entries())) : new this._headersClass(d);
  }
  headers() {
    const e = this._preferDSID ? "X-Dsid" : "media-user-token", n = this.baseHeaders();
    return n.set("Authorization", "Bearer " + this.accessToken), n.set("Content-Type", "application/json"), n.set(e, "" + this.musicUserToken), this._isQA && void 0 !== this._traceTag && n.set("Data-Trace-Tag", this._traceTag), n;
  }
  _generateFetchOptions(e) {
    return _objectSpread$F({}, this._fetchOptions, e);
  }
  constructor(e) {
    var n, d, h, p;
    this.mode = Ar.AUTO, this._isQA = false, this._logInfo = false, this._preferDSID = false, this._accessToken = e.accessToken, this._clientId = e.clientId, this._eventType = e.eventType, this._fetch = null !== (n = e.fetch) && void 0 !== n ? n : fetch, this._fetchOptions = null !== (d = e.fetchOptions) && void 0 !== d ? d : {}, this._headersClass = null !== (h = e.headersClass) && void 0 !== h ? h : Headers, this._isQA = null !== (p = e.isQA) && void 0 !== p && p, this._logInfo = e.logInfo || this._isQA, this._musicUserToken = e.musicUserToken, this._preferDSID = e.preferDSID, this._sourceType = e.sourceType, this._traceTag = e.traceTag;
  }
}
