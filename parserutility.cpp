#include "parserutility.h"

ParserUtility::ParserUtility()
{

}
class ParserUtility {
  static parseTimeStamp(e) {
    function computeSeconds(e) {
      const [n, d, h, p] = e.map(e => e ? parseInt("" + e) : 0);
      return 3600 * n + 60 * d + h + p / 1e3;
    }
    const n = /^(\d+):(\d{2})(:\d{2})?\.(\d{3})/.exec(e);
    return n ? n[3] ? computeSeconds([n[1], n[2], n[3].substring(1), n[4]]) : parseInt(n[1]) > 59 ? computeSeconds([n[1], n[2], null, n[4]]) : computeSeconds([null, n[1], n[2], n[4]]) : null;
  }
  static parseContent(e, n, g) {
    let b = n.text;
    function nextToken() {
      if (!b) return null;
      const e = /^([^<]*)(<[^>]+>?)?/.exec(b);
      return n = e[1] ? e[1] : e[2], b = b.substr(n.length), n;
      var n;
    }
    function createElement(n, d, y) {
      const b = h[n];
      if (!b) return null;
      const _ = e.document.createElement(b);
      _.dataset.localName = b;
      const T = p[n];
      if (T && y && (_[T] = y.trim()), d) if (g[d]) {
        const e = function (e) {
          let n = "";
          for (const d in e) n += m[d] ? m[d] : d + ":" + e[d] + ";";
          return n;
        }(g[d]);
        _.setAttribute("style", e);
      } else console.info(`WebVTT: parseContent: Style referenced, but no style defined for '${d}'!`);
      return _;
    }
    const _ = e.document.createElement("div"), T = [];
    let S, P, E = _;
    for (; null !== (S = nextToken());) if ("<" !== S[0]) E.appendChild(e.document.createTextNode(S.replace(/&(amp|lt|gt|lrm|rlm|nbsp);/g, unescape1))); else {
      if ("/" === S[1]) {
        T.length && T[T.length - 1] === S.substr(2).replace(">", "") && (T.pop(), E = E.parentNode);
        continue;
      }
      const n = ParserUtility.parseTimeStamp(S.substr(1, S.length - 2));
      let d;
      if (n) {
        d = e.document.createProcessingInstruction("timestamp", n.toString()), E.appendChild(d);
        continue;
      }
      if (P = /^<([^.\s/0-9>]+)(\.[^\s\\>]+)?([^>\\]+)?(\\?)>?$/.exec(S), !P) continue;
      if (d = createElement(P[1], P[2], P[3]), !d) continue;
      if (!(!y[d.dataset.localName] || y[d.dataset.localName] === E.dataset.localName)) continue;
      P[2], T.push(P[1]), E.appendChild(d), E = d;
    }
    return _;
  }
}
