#include "webvttparser.h"

WebVTTParser::WebVTTParser()
{

}
class WebVTTParser {
  static StringDecoder() {
    return {decode: e => {
      if (!e) return "";
      if ("string" != typeof e) throw new Error("Error - expected string data.");
      return decodeURIComponent(encodeURIComponent(e));
    }};
  }
  reportOrThrowError(e) {
    if (!(e instanceof ParsingError && "function" == typeof this.onparsingerror)) throw e;
    this.onparsingerror(e);
  }
  parseOptions(e, n, d, h) {
    const p = h ? e.split(h) : [e];
    for (const y of p) {
      if ("string" != typeof y) continue;
      const e = y.split(d);
      if (2 !== e.length) continue;
      n(e[0], e[1]);
    }
  }
  parseCue(e, n, d) {
    const h = e, consumeTimeStamp = () => {
      const n = Hi.default.parseTimeStamp(e);
      if (null === n) throw new ParsingError(ParsingError.Errors.BadTimeStamp, "Malformed timestamp: " + h);
      return e = e.replace(/^[^\sa-zA-Z-]+/, ""), n;
    }, skipWhitespace = () => {
      e = e.replace(/^\s+/, "");
    };
    if (skipWhitespace(), n.startTime = consumeTimeStamp(), skipWhitespace(), "-->" !== e.substr(0, 3)) throw new ParsingError(ParsingError.Errors.BadTimeStamp, "Malformed time stamp (time stamps must be separated by '-->'): " + h);
    e = e.substr(3), skipWhitespace(), n.endTime = consumeTimeStamp(), skipWhitespace(), ((e, n) => {
      const h = new Settings;
      this.parseOptions(e, (e, n) => {
        let p, y;
        switch (e) {
          case "region":
            for (let p = d.length - 1; p >= 0; p--) if (d[p].id === n) {
              h.set(e, d[p].region);
              break;
            }
            break;
          case "vertical":
            h.alt(e, n, ["rl", "lr"]);
            break;
          case "line":
            p = n.split(","), y = "allow-forms", h.integer(e, y), h.percent(e, y) && h.set("snapToLines", false), h.alt(e, y, ["auto"]), 2 === p.length && h.alt("lineAlign", "allow-popups", ["start", "middle", "center", "end"]);
            break;
          case "position":
            if (p = n.split(","), h.percent(e, "allow-forms"), 2 === p.length) {
              let e = ["line-left", "line-right", "center", "auto", "left", "start", "middle", "end", "right"];
              h.alt("positionAlign", "allow-popups", e);
            }
            break;
          case "size":
            h.percent(e, n);
            break;
          case "align":
            let m = ["start", "center", "end", "left", "right", "middle"];
            h.alt(e, n, m);
        }
      }, /:/, /\s/), n.region = h.get("region", null), n.vertical = h.get("vertical", ""), n.line = h.get("line", void 0 === n.line ? "auto" : n.line);
      const p = h.get("lineAlign", "start");
      n.lineAlign = "center" === p || "middle" === p ? this.middleOrCenter : p, n.snapToLines = h.get("snapToLines", true), n.size = h.get("size", 100);
      const y = h.get("align", "center");
      n.align = "center" === y || "middle" === y ? this.middleOrCenter : y, n.position = h.get("position", "auto");
      let m = h.get("positionAlign", {start: "start", left: "start", center: "center", middle: "middle", right: "end", end: "end"}, n.align);
      n.positionAlign = "center" === m || "middle" === m ? this.middleOrCenter : {start: "start", "line-left": "start", left: "start", center: "center", middle: "middle", "line-right": "end", right: "end", end: "end"}[m];
    })(e, n);
  }
  parseRegion(e) {
    const n = new Settings;
    if (this.parseOptions(e, (e, d) => {
      switch (e) {
        case "id":
          n.set(e, d);
          break;
        case "width":
          n.percent(e, d);
          break;
        case "lines":
          n.integer(e, d);
          break;
        case "regionanchor":
        case "viewportanchor":
          {
            const h = d.split(",");
            if (2 !== h.length) break;
            const p = new Settings;
            if (p.percent("x", h[0]), p.percent("y", h[1]), !p.has("x") || !p.has("y")) break;
            n.set(e + "X", p.get("x")), n.set(e + "Y", p.get("y"));
            break;
          }
        case "scroll":
          n.alt(e, d, ["up"]);
      }
    }, /=/, /\s/), n.has("id")) {
      const e = new qi.VTTRegion;
      e.width = n.get("width", 100), e.lines = n.get("lines", 3), e.regionAnchorX = n.get("regionanchorX", 0), e.regionAnchorY = n.get("regionanchorY", 100), e.viewportAnchorX = n.get("viewportanchorX", 0), e.viewportAnchorY = n.get("viewportanchorY", 100), e.scroll = n.get("scroll", ""), this.onregion && this.onregion(e), this.regionList.push({id: n.get("id"), region: e});
    }
  }
  parseStyle(e) {
    const parseStyles = e => {
      const n = {}, d = e.split(";");
      for (let h = 0; h < d.length; h++) if (d[h].includes(":")) {
        const e = d[h].split(":", 2), p = e[0].trim(), y = e[1].trim();
        "" !== p && "" !== y && (n[p] = y);
      }
      return n;
    }, n = e.split("}");
    n.pop();
    for (const d of n) {
      let e = null, n = null;
      const h = d.split("{");
      h[0] && (e = h[0].trim()), h[1] && (n = parseStyles(h[1])), e && n && (this._styles[e] = n);
    }
    this.onStylesParsedCallback && this.onStylesParsedCallback(this._styles);
  }
  parseHeader(e) {
    this.parseOptions(e, function (e, n) {
      switch (e) {
        case "Region":
          this.parseRegion(n);
      }
    }, /:/);
  }
  parse(e) {
    e && (this.buffer += this.decoder.decode(e, {stream: true}));
    const collectNextLine = () => {
      const e = this.buffer;
      let n = 0;
      const calculateBreakPosition = (e, n) => {
        const d = {start: -1, length: -1};
        if ("\r" === e[n]) d.start = n, d.length = 1; else if ("\n" === e[n]) d.start = n, d.length = 1; else if ("<" === e[n] && n + 1 < e.length && "b" === e[n + 1] && n + 2 < e.length && "r" === e[n + 2]) {
          let h = n + 2;
          for (; h < e.length && ">" !== e[h++];) ;
          d.start = n, d.length = h - n;
        }
        return d;
      };
      let d = {start: e.length, length: 0};
      for (; n < e.length;) {
        const h = calculateBreakPosition(e, n);
        if (h.length > 0) {
          d = h;
          break;
        }
        ++n;
      }
      const h = e.substr(0, d.start);
      return this.buffer = e.substr(d.start + d.length), h;
    };
    try {
      let e;
      if ("INITIAL" === this.state) {
        if (!/\r\n|\n/.test(this.buffer)) return this;
        this.alreadyCollectedLine = "", e = collectNextLine();
        const n = /^(Ã¯Â»Â¿)?WEBVTT([ \t].*)?$/.exec(e);
        if (!n || !n[0]) throw new ParsingError(ParsingError.Errors.BadSignature);
        this.state = "HEADER";
      }
      for (; this.buffer;) {
        if (!/\r\n|\n/.test(this.buffer)) return this;
        switch (this.alreadyCollectedLine ? (e = this.alreadyCollectedLine, this.alreadyCollectedLine = "") : e = collectNextLine(), this.state) {
          case "HEADER":
            e.includes(":") ? this.parseHeader(e) : e || (this.state = "ID");
            continue;
          case "NOTE":
            e || (this.state = "ID");
            continue;
          case "STYLE":
            e ? this.styleCollector += e : (this.parseStyle(this.styleCollector), this.state = "ID", this.styleCollector = "");
            continue;
          case "ID":
            if (/^NOTE($|[ \t])/.test(e)) {
              this.state = "NOTE";
              break;
            }
            if (/^STYLE($|[ \t])/.test(e)) {
              this.state = "STYLE";
              break;
            }
            if (!e) continue;
            if (this.cue = new Wi.VTTCue(0, 0, ""), this.state = "CUE", !e.includes("-->")) {
              this.cue.id = e;
              continue;
            }
          case "CUE":
            try {
              this.parseCue(e, this.cue, this.regionList);
            } catch (Mr) {
              this.reportOrThrowError(Mr), this.cue = null, this.state = "BADCUE";
              continue;
            }
            this.state = "CUETEXT";
            continue;
          case "CUETEXT":
            {
              const n = e.includes("-->");
              if (!e || n) {
                this.alreadyCollectedLine = e, this.oncue && this.oncue(this.cue), this.cue = null, this.state = "ID";
                continue;
              }
              this.cue.text && (this.cue.text += "\n"), this.cue.text += e;
              continue;
            }
          case "BADCUE":
            e || (this.state = "ID");
            continue;
        }
      }
    } catch (Mr) {
      this.reportOrThrowError(Mr), "CUETEXT" === this.state && this.cue && this.oncue && this.oncue(this.cue), this.cue = null, this.state = "INITIAL" === this.state ? "BADWEBVTT" : "BADCUE";
    }
    return this;
  }
  flush() {
    try {
      if (this.buffer += this.decoder.decode(), (this.cue || "HEADER" === this.state) && (this.buffer += "\n\n", this.parse()), "INITIAL" === this.state) throw new ParsingError(ParsingError.Errors.BadSignature);
    } catch (Mr) {
      this.reportOrThrowError(Mr);
    }
    return this.onflush && this.onflush(), this;
  }
  styles() {
    return this._styles;
  }
  constructor(e, n, d) {
    this.window = e, this.state = "INITIAL", this.styleCollector = "", this.buffer = "", this.decoder = n || new TextDecoder("utf8"), this.regionList = [], this.alreadyCollectedLine = "", this.onStylesParsedCallback = d, this._styles = {}, this.middleOrCenter = "center";
    const h = new Wi.VTTCue(0, 0, "middleOrCenter");
    try {
      h.align = "center", "center" !== h.align && (this.middleOrCenter = "middle");
    } catch (Mr) {
      this.middleOrCenter = "middle";
    }
  }
}
