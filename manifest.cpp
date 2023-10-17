#include "manifest.h"

Manifest::Manifest()
{

}
class Manifest extends Notifications {
  parse() {
    const e = this._item, n = this._data;
    if (Xt !== Ft.FAIRPLAY || shouldForceAudioMse()) if (this._detectKeyTags(), e.hasOffersHlsUrl) this._segmentList.extractHlsOffersSegments(n, e.assetURL); else if (e.isLiveRadioStation) {
      this._segmentList.extractLiveRadioSegments(n, e.assetURL);
      const [, d] = this._data.match(Na);
      Ct.debug(`manifest: setting up manifest refresh interval at ${d} seconds`);
      const h = 1e3 * parseInt(d, 10);
      this._manifestRefreshInterval = setInterval(this.liveRadioRefresh, h);
    } else this._segmentList.extractByteRangeSegments(n, e.assetURL);
  }
  static load(e, n = true) {
    var d = this;
    return _asyncToGenerator$H(function* () {
      Ct.debug("loading manifest for item", e.title);
      const h = e.assetURL;
      let p;
      const y = getSessionStorage(), m = !!y && n;
      if (m && (p = null == y ? void 0 : y.getItem(h), p)) return new d(p, e);
      const g = (new Date).getTime();
      p = yield _loadManifestData.apply(this, arguments);
      const b = new d(p, e);
      return b.downlink = function (e, n) {
        return 8 * n.length / (((new Date).getTime() - e) / 1e3) / 1024;
      }(g, p), m && (null == y || y.setItem(h, p)), Promise.resolve(b);
    })();
  }
  get downlink() {
    return this._downlink;
  }
  set downlink (e) {
    this._downlink = e;
  }
  get mediaItem() {
    return this._item;
  }
  liveRadioRefresh() {
    var e = this;
    return _asyncToGenerator$H(function* () {
      const n = yield _loadManifestData.apply(this, arguments);
      e._data = n, e._detectKeyTags(), e._segmentList.extractLiveRadioSegments(n, e._url), e.dispatchEvent(zt.manifestParsed);
    })();
  }
  segmentsForTimeRange(e) {
    const n = Math.floor(e.start / 10) + 1, d = Math.floor(e.end / 10) + 1, {segments: h} = this;
    return [h[0], ...h.slice(n, d + 1)];
  }
  get segments() {
    return this._segmentList.segments;
  }
  get extURI() {
    if (!this._extURI) {
      const e = this._data.match(ja);
      Ct.debug("manifest: EXT_X_KEY_URI matches", e), this._extURI = e && e[1] || void 0;
    }
    return this._extURI;
  }
  get keyValues() {
    let e = this._modernKeys;
    return e.length || (e = this._legacyKeys), e;
  }
  _detectKeyTags() {
    const e = this.keyValues;
    e.length && this.dispatchEvent(Ma.keysParsed, {item: this.mediaItem, keys: e});
  }
  get _legacyKeys() {
    const e = this._data.match(ja);
    Ct.debug("manifest: EXT_X_KEY_URI matches", e);
    const n = e && e[1] || void 0;
    this._extURI = n;
    const d = [];
    return n && d.push({keyFormat: Jt.WIDEVINE, dataUri: n}), d;
  }
  get _modernKeys() {
    let e;
    Ua.lastIndex = 0;
    const n = [];
    for (; e = Ua.exec(this._data);) {
      const [d, h, p] = e;
      n.push({keyFormat: p, dataUri: h});
    }
    return n;
  }
  stop() {
    this._manifestRefreshInterval && clearInterval(this._manifestRefreshInterval);
  }
  constructor(e, n) {
    super([zt.manifestParsed, Ma.keysParsed]), this._downlink = 0, this._segmentList = new SegmentList, this._data = e, this._item = n, this._url = n.assetURL;
  }
}
