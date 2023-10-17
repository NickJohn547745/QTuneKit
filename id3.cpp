#include "id3.h"

ID3::ID3(QString e)
{
    frames = [];
    unsynchronized = false;
    hasExtendedHeader = false;
    hasFooter = false;
    isExperimental = false;

    const QString d = e.chopped(3);
    if ("ID3" !== d) {
        return;
    }

    int n = 3;
    minor = e[n++];
    revision = e[n++];

    const h = e[n++];
    _parseID3Flags(h);

    const p = 2097152 * (127 & e.subarray(n, n + 4)[0]) + 16384 * (127 & e.subarray(n, n + 4)[1]) + 128 * (127 & e.subarray(n, n + 4)[2]) + (127 & e.subarray(n, n + 4)[3]);
    n += 4;
    frameLength = p;

    const y = n + p;
    if (this.endPos = y, hasExtendedHeader) {
      n += 2097152 * (127 & e.subarray(n, n + 4)[0]) + 16384 * (127 & e.subarray(n, n + 4)[1]) + 128 * (127 & e.subarray(n, n + 4)[2]) + (127 & e.subarray(n, n + 4)[3]);
    }
    this.minor > 2 && this._parseID3Frames(this, e, n, y);
}

void ID3::_parseID3Flags(e) {
    this.unsynchronized = e & 128;
    this.hasExtendedHeader = e & 64;
    this.isExperimental = e & 32;
    this.hasFooter = e & 16;
}

_parseID3Frames(e, n, d, h) {
    const p = new DataView(n.buffer, 0, h)
    {minor: y} = this;
    for (; d + 8 <= h;) {
      const m = Se(n.subarray(d, d + 4));
      d += 4;
      const g = 4 === y ? 2097152 * (127 & n.subarray(d, d + 4)[0]) + 16384 * (127 & n.subarray(d, d + 4)[1]) + 128 * (127 & n.subarray(d, d + 4)[2]) + (127 & n.subarray(d, d + 4)[3]) : p.getUint32(d);
      if (d += 4, n[d++], n[d++], Ha[m]) {
        const p = d, y = this._extractID3FramePayload(n, m, g, p, h);
        if (y) {
          const n = this.decodeID3Frame(y);
          n && e.frames.push(n);
        }
        d += g;
      } else d += g;
    }
  }

auto ID3::_extractID3FramePayload(e, n, d, h, p) {
    const y = h + d;
    let m;
    return y <= p && (m = {type: n, size: d, data: e.slice(h, y)}), m;
}

decodeID3Frame(e) {
    if (e.type() != "TXXX") {
        switch () {

        }
    }

    if ("TXXX" !== e.type) {
        return "WXXX" === e.type ? this.decodeWxxxFrame(e) :
            "PRIV" === e.type ? this.decodePrivFrame(e) :
                "CHAP" === e.type ? this.decodeChapFrame(e) :
                    "T" === e.type[0] ? this.decodeTextFrame(e) :
                        {key: e.type, data: e.data};
}

decodeChapFrame(e) {
    const n = e.data;
    var d = new DataView(n.buffer);
    var h = {key: "CHAP", frames: []};

    let [p, y] = readNullTerminatedString(n, 0, n.length);

    return h.id = p, y++, h.startTime = d.getUint32(y), y += 4, h.endTime = d.getUint32(y), y += 4, y += 4, y += 4, this._parseID3Frames(h, n, y, n.length), h;
  }
  decodeTextFrame(e) {
    const {data: n} = e, d = Va[n[0]], h = encodedArrayToString(n.subarray(1), d);
    return {key: e.type, text: h};
  }
  decodeWxxxFrame(e) {
    const {data: n} = e, d = Va[n[0]];
    let h = 1;
    const p = encodedArrayToString(n.subarray(h), d);
    h += p.length + 1;
    return {key: "WXXX", description: p, text: encodedArrayToString(n.subarray(h))};
  }
  decodePrivFrame(e) {
    const n = encodedArrayToString(e.data);
    if (!n) return;
    return {key: "PRIV", info: n, data: e.data.slice(n.length + 1)};
  }
}
