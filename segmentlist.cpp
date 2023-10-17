#include "segmentlist.h"

SegmentList::SegmentList()
{

}
class SegmentList {
  get segments() {
    return this._segments;
  }
  addSegment(e, n) {
    this._addedSegments[n] || (Ct.debug("Adding segment", n), this._segments.push(e), this._addedSegments[n] = true);
  }
  extractLiveRadioSegments(e, n) {
    this._extractContinuousSegments(Ca, e, n);
  }
  extractHlsOffersSegments(e, n) {
    this._extractContinuousSegments(Da, e, n);
  }
  _extractContinuousSegments(e, n, d) {
    if (!n || !e.test(n)) return;
    let h;
    for (e.lastIndex = 0; h = e.exec(n);) {
      const e = h[0].startsWith("#EXT-X-MAP") ? h[2] : h[1], n = rewriteLastUrlPath(d, e), p = h[0].startsWith("#EXT-X-MAP");
      this.addSegment(new ContinuousSegment(n, p), e);
    }
  }
  extractByteRangeSegments(e, n) {
    if (!e || !Aa.test(e)) return;
    const d = function (e) {
      if (!e || !Ra.test(e)) return;
      const [, n] = e.match(Ra);
      return n.split(",").reduce((e, n) => {
        const [d, h] = n.split("=");
        return e[d.toLowerCase()] = h.replace(/\"/gi, ""), e;
      }, {});
    }(e);
    var h;
    const p = null !== (h = n.split("/").pop()) && void 0 !== h ? h : "", y = n.replace(p, d.uri), [m, g] = d.byterange.split("@"), b = new ByteRangeSegment({url: y, startByte: g, length: m});
    var _;
    this.addSegment(b, b.range), (null !== (_ = e.match(Aa)) && void 0 !== _ ? _ : []).forEach(e => {
      const [, n, d] = e.match(/^#EXT-X-BYTERANGE:(\d+)@(\d+)\n/), h = new ByteRangeSegment({url: y, startByte: d, length: n});
      this.addSegment(h, h.range);
    });
  }
  constructor() {
    this._segments = [], this._addedSegments = {};
  }
}
