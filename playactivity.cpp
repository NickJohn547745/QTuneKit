#include "playactivity.h"

PlayActivity::PlayActivity()
{

}
class PlayActivity {
  get mode() {
    return this.sender.mode;
  }
  set mode (e) {
    this.sender.mode = e;
  }
  get privateEnabled() {
    return this._paf.privateEnabled;
  }
  set privateEnabled (e) {
    this._paf.privateEnabled = e;
  }
  get timedMetadata() {
    return this._timedMetadataTracker.currentValue;
  }
  clearTimedMetadata() {
    return this._timedMetadataTracker.clear();
  }
  setTimedMetadata(e, n) {
    var d = this;
    return _asyncToGenerator$W(function* () {
      yield d._timedMetadataTracker.ping(e, n);
    })();
  }
  activate(n = false) {
    var d = this;
    return _asyncToGenerator$W(function* () {
      if (n) try {
        yield d.flush();
      } catch (p) {
        if (!(e => (e => {
          switch (typeof e) {
            case "string":
              return e;
            case "object":
              return e.message ? "string" != typeof e.message ? "" : e.message : "";
            default:
              return "";
          }
        })(e).includes("send() called without any data"))(p)) throw p;
      }
      const h = d.timeline.last;
      if (h && h.endReasonType === e.PlayActivityEndReasonType.EXITED_APPLICATION) return d.timeline.pop();
    })();
  }
  exit(n = 0) {
    var d = this;
    return _asyncToGenerator$W(function* () {
      yield d.stop(n, e.PlayActivityEndReasonType.EXITED_APPLICATION);
    })();
  }
  pause(n = 0) {
    var d = this;
    return _asyncToGenerator$W(function* () {
      yield d.stop(n, e.PlayActivityEndReasonType.PLAYBACK_MANUALLY_PAUSED);
    })();
  }
  pingTimedMetadata(n, d, h = this.previousDescriptor) {
    var p = this;
    return _asyncToGenerator$W(function* () {
      yield p._addToTimeline(_objectSpreadProps$g(_objectSpread$t({}, h), {position: n, endReasonType: e.PlayActivityEndReasonType.NOT_APPLICABLE, eventType: wr.PLAY_END, itemType: Or.TIMED_METADATA_PING, timedMetadata: d}));
    })();
  }
  play(e, n = 0) {
    var d = this;
    return _asyncToGenerator$W(function* () {
      const h = d.timeline.length > 0;
      if (void 0 === e) {
        if (!h) return;
        const e = d.previousDescriptor;
        return e.eventType === wr.PLAY_END && delete e.endReasonType, void (yield d._addToTimeline(_objectSpreadProps$g(_objectSpread$t({}, d.sanitizePreviousDescriptor(e)), {eventType: wr.PLAY_START})));
      }
      if (h) {
        const e = d.previousDescriptor;
        if (d._machine.matches("playing") && !(({id: e, reporting: n = true, eventType: d}) => ("-1" === e || !n) && d === wr.PLAY_END)(e)) return Promise.reject(new Error("The play() method was called without a previous stop() or pause() call."));
      }
      yield d._addToTimeline(_objectSpreadProps$g(_objectSpread$t({}, e), {eventType: wr.PLAY_START, position: n}));
    })();
  }
  scrub(n = 0, d = e.PlayActivityEndReasonType.SCRUB_BEGIN) {
    var h = this;
    return _asyncToGenerator$W(function* () {
      yield h._addToTimeline(_objectSpreadProps$g(_objectSpread$t({}, h.sanitizePreviousDescriptor(h.previousDescriptor)), {eventType: wr.PLAY_END, endReasonType: d, position: n}));
    })();
  }
  skip(n, d = e.PlayActivityEndReasonType.TRACK_SKIPPED_FORWARDS, h = 0) {
    var p = this;
    return _asyncToGenerator$W(function* () {
      yield p.stop(h, d), yield p.play(n);
    })();
  }
  stop(n = 0, d = e.PlayActivityEndReasonType.NATURAL_END_OF_TRACK) {
    var h = this;
    return _asyncToGenerator$W(function* () {
      let p = h.previousDescriptor;
      if (p.endReasonType === e.PlayActivityEndReasonType.EXITED_APPLICATION && (yield h.timeline.pop(), empty(h._cookieJar, "amupaee"), p = h.previousDescriptor), h._machine.matches("playing")) {
        const e = _objectSpreadProps$g(_objectSpread$t({}, h.sanitizePreviousDescriptor(p)), {eventType: wr.PLAY_END, endReasonType: d, position: n, timedMetadata: h._timedMetadataTracker.currentValue});
        yield h._addToTimeline(e);
      }
    })();
  }
  build(e, n) {
    if (void 0 === e && void 0 === n && Dt.warn("You are calling build() from a stateful PAF client. Please, use a stateless client or exit(), pause(), play(), scrub(), skip() or stop() instead."), void 0 === e) {
      if (0 === this.timeline.length) throw new Error("build() called without a play activity descriptor");
      e = this.timeline.last;
    }
    if (void 0 === n) {
      if (void 0 === (n = this.timeline.before(e)) && e.eventType === wr.PLAY_END) throw new Error("Cannot build() for PLAY_END descriptors without previous descriptors");
      n = null != n && n;
    }
    return this._paf.build(_objectSpreadProps$g(_objectSpread$t({}, e), {timedMetadata: this.timedMetadata}), n);
  }
  addForPlayParams(e, n, d, h = 0, p = {}) {
    var y = this;
    return _asyncToGenerator$W(function* () {
      yield y._addToTimeline(y.buildDescriptorForPlayParams(e, n, d, h, p));
    })();
  }
  buildDescriptorForPlayParams(e, n, d, h = 0, p = {}) {
    const y = "stream" === e.format ? Or.STREAM : Or.ITUNES_STORE_CONTENT;
    return normalizePlayActivityDescriptor(_objectSpread$t(_objectSpreadProps$g(_objectSpread$t({}, e), {container: d, duration: h, eventType: n, itemType: y}), p));
  }
  flush() {
    return this.sender.flush();
  }
  _addToTimeline(e) {
    var n = this;
    return _asyncToGenerator$W(function* () {
      e = _objectSpreadProps$g(_objectSpread$t({}, e), {timestamp: Date.now()});
      const d = n.timeline.length > 0 && n.timeline.last;
      yield n.timeline.add(e);
      const h = n.build(e, d);
      yield n.send(h, e);
    })();
  }
  get previousDescriptor() {
    const e = this.timeline.last;
    if (void 0 === e) throw new Error("A method was called without a previous descriptor");
    return exceptFields(e, "timestamp");
  }
  buildForPlayParams(e, n, d, h = 0, p = {}, y = false) {
    return Dt.warn("You are using buildsForPlayParams from a stateful PlayActivity. Please, use StatelessPlayActivity instead"), this._paf.buildForPlayParams(e, n, d, h, p, y);
  }
  send(e, n) {
    e = ensureArray(e);
    const d = normalizePlayActivityDescriptor(n);
    return e.forEach(e => this._machine.transition(d, e)), this.sender.send(e);
  }
  sanitizePreviousDescriptor(e) {
    let n = deepClone(e);
    return n.itemType === Or.TIMED_METADATA_PING && (n = exceptFields(n, "itemType")), n;
  }
  constructor(e, n, d, h) {
    this.timeline = new Timeline, this._paf = new StatelessPlayActivity(e, n, d, h), this._cookieJar = createCookieJar(null == h ? void 0 : h.cookieJar), this.sender = new PlayActivityBatchableSender(this._paf.sender, this._cookieJar), this._machine = new MPAFStateMachine, this._timedMetadataTracker = new TimedMetadataTracker(this);
  }
}
