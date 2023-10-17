#include "lyricsplayactivity.h"

LyricsPlayActivity::LyricsPlayActivity()
{

}
class LyricsPlayActivity extends PlayActivityBase {
  get state() {
    return this._machine.state.value;
  }
  play(e) {
    var n = this;
    return _asyncToGenerator$_(function* () {
      var d;
      if ("playing" === n.state) throw Error("lyrics are already being displayed. Did you forget to stop them?");
      if (void 0 === e) throw Error("Missing descriptor for lyrics play");
      Dt.info(`Staring tracking: lyricsId=${null === (d = e.lyricDescriptor) || void 0 === d ? void 0 : d.id}, itemId=${e.id}, catalogId=${e.catalogId}`), n.startDescriptor = e, n._machine.send({type: "play"});
    })();
  }
  stop() {
    var e = this;
    return _asyncToGenerator$_(function* () {
      var n;
      if ("playing" !== e.state) throw Error("lyrics are not being displayed. Did you forget to display them?");
      if (void 0 === e.startDescriptor) throw Error("Missing start descriptor for lyrics stop");
      Dt.info(`Stopping tracking: lyricsId=${null === (n = e.startDescriptor.lyricDescriptor) || void 0 === n ? void 0 : n.id}, itemId=${e.startDescriptor.id}, catalogId=${e.startDescriptor.catalogId}`), e._machine.send({type: "stop"});
      const d = e._machine.state.context.duration, h = JSON.parse(JSON.stringify(e.startDescriptor));
      h.lyricDescriptor = _objectSpreadProps$i(function (e) {
        for (var n = 1; n < arguments.length; n++) {
          var d = null != arguments[n] ? arguments[n] : {}, h = Object.keys(d);
          "function" == typeof Object.getOwnPropertySymbols && (h = h.concat(Object.getOwnPropertySymbols(d).filter(function (e) {
            return Object.getOwnPropertyDescriptor(d, e).enumerable;
          }))), h.forEach(function (n) {
            n in e ? Object.defineProperty(e, n, {value: d[n], enumerable: true, configurable: true, writable: true}) : e[n] = d[n], e;
          });
        }
        return e;
      }({}, h.lyricDescriptor), {duration: Math.round(d)}), Dt.debug("Clearing tracked descriptor"), e.startDescriptor = void 0;
      const p = e.build(h, false);
      try {
        Dt.debug("Sending PAF request with data payload"), yield e.send(p), Dt.debug("Done sending PAF request");
      } catch (z) {
        console.error("Error sending Lyrics PAF request: " + z.message), Dt.error("Error sending Lyrics PAF request: " + z.message);
      }
    })();
  }
  exit() {
    return _asyncToGenerator$_(function* () {})();
  }
  build(e, n) {
    return ((e, n, d) => {
      if (void 0 === n) throw new Error("called without a play activity descriptor");
      const h = _objectSpreadProps$k(_objectSpread$x({}, n), {eventType: wr.LYRIC_DISPLAY});
      return ((e, ...n) => n.reduce((e, n) => n(e), e))(_objectSpreadProps$k(_objectSpread$x({}, buildPlayActivityData$1(e, h, d, false)), {"media-duration-in-milliseconds": 0, "media-type": Ir.AUDIO, "start-position-in-milliseconds": 0, "play-mode": {"auto-play-mode": 0, "repeat-play-mode": 0, "shuffle-play-mode": 0}}), e => exceptFields(e, "character-display-count", "event-reason-hint-type", "reco-data"));
    })(this, e, n);
  }
  constructor(e, n, d, h) {
    super(e, n, d, h), this._machine = v(s({id: "lpaf", initial: "idle", context: {initialShowTime: -1, duration: -1}, states: {idle: {entry: o(e => _objectSpreadProps$j(_objectSpread$w({}, e), {initialShowTime: void 0, duration: Gr() - e.initialShowTime})), on: {play: "playing"}}, playing: {entry: o(e => _objectSpreadProps$j(_objectSpread$w({}, e), {initialShowTime: Gr()})), on: {stop: "idle"}}}})).start();
  }
}
