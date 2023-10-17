#include "emsg.h"

Emsg::Emsg()
{

}
class Emsg {
  get length() {
    return this.data.length;
  }
  get elementPresentationTime() {
    const {presentationTime: e, timeScale: n} = this;
    return e && n ? Math.round(e / n) : NaN;
  }
  get timedMetadata() {
    var e;
    if (this._timedMetadata) return this._timedMetadata;
    const n = null === (e = this.id3) || void 0 === e ? void 0 : e.frames;
    return n ? (this._timedMetadata = new TimedMetadata(n), this._timedMetadata) : void 0;
  }
  constructor(e) {
    this.data = e;
    const n = new DataView(e.buffer);
    let d = 8;
    if (1 !== e[d]) return;
    d += 4, this.timeScale = n.getUint32(d), d += 4;
    const h = n.getUint32(d);
    d += 4;
    const p = n.getUint32(d);
    if (d += 4, this.presentationTime = Math.pow(2, 32) * h + p, !Number.isSafeInteger(this.presentationTime)) throw this.presentationTime = Number.MAX_SAFE_INTEGER, new Error("Failed to create 64 bit integer");
    this.eventDuration = n.getUint32(d), d += 4, this.id = n.getUint32(d), d += 4;
    const [y, m] = readNullTerminatedString(e, d);
    d += m + 1, this.schemeIdUri = y;
    const [g, b] = readNullTerminatedString(e, d);
    d += b + 1, this.payload = e.subarray(d, e.byteLength), this.id3 = new ID3(this.payload);
  }
}
