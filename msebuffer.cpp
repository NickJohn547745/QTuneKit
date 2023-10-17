#include "msebuffer.h"

MseBuffer::MseBuffer()
{

}
class MseBuffer {
  onSourceOpen() {
    Ja.debug("mediaSource open handler");
    const {mediaSource: e} = this;
    if (e.activeSourceBuffers.length > 0) return void Ja.debug("not adding new source buffer");
    Ja.debug("adding new source buffer");
    const n = e.addSourceBuffer(Ht);
    this.sourceBuffer = n, n.addEventListener("updateend", this.updateEndHandler);
    const {clip: d, hasAppendWindowSupport: h} = this;
    d && (h ? (Ja.debug("appendWindowStart/End", d.start, d.end), n.appendWindowStart = d.start, n.appendWindowEnd = d.end) : (Ja.debug("seeking for clip", d.start), asAsync(this.seek(d.start)))), this.updateSegmentToFetch(0, true);
  }
  setNextManifest(e) {
    Ja.debug("setting next manifest for ", e.mediaItem.title), this.nextSeamlessTransition ? (Ja.debug("abandoning transition scheduled for " + this.nextSeamlessTransition), this.revertSeamlessTransition(true), this.playbackTimeline.next = {manifest: e}) : (this.playbackTimeline.next = {manifest: e}, this.isFullyBuffered && (Ja.debug("current song is fully buffered, beginning transition to next"), this.transitionToNextManifest()));
  }
  isItemPlaying(e) {
    var n, d;
    const {playbackTimeline: h} = this, p = this.nextSeamlessTransition ? null === (n = h.previous) || void 0 === n ? void 0 : n.manifest.mediaItem : null === (d = h.current) || void 0 === d ? void 0 : d.manifest.mediaItem;
    return !!p && (Ja.debug(`isItemPlaying ${e.title}, ${p.title}, ${e.id === p.id}`), e.id === p.id);
  }
  get currentItem() {
    return this.manifest.mediaItem;
  }
  get playableUrl() {
    let e = this._playableUrl;
    return e || (e = window.URL.createObjectURL(this.mediaSource), Ja.debug("created url", e), this._playableUrl = e, e);
  }
  get segments() {
    const {manifest: e, clip: n} = this;
    return n ? e.segmentsForTimeRange(n) : e.segments || [];
  }
  get currentTime() {
    return this._currentTime;
  }
  set currentTime (e) {
    if (e += this.currentTimestampOffset, this._currentTime === e) return;
    const {nextSeamlessTransition: n} = this;
    if (n && e >= n) {
      var d, h;
      Ja.debug("setting offset to", n), this.currentTimestampOffset = n || 0, this.nextSeamlessTransition = void 0, this.duration = this.manifest.mediaItem.playbackDuration / 1e3, Ja.debug("buffer setting duration to", this.duration);
      const e = {previous: null === (d = this.playbackTimeline.previous) || void 0 === d || null === (h = d.manifest) || void 0 === h ? void 0 : h.mediaItem, current: this.manifest.mediaItem};
      Ja.debug("dispatching seamless audio transition", e), this.dispatcher.publish($a, e);
    }
    this._currentTime = e;
    const {isOverBufferLimit: p, timeToTrim: y} = this, m = e > this.timeToTrim;
    p && m && (Ja.debug("buffer over limit, trimming to ", y), this.removeToTime(y), this.timeToTrim += 10);
  }
  get hasAppendWindowSupport() {
    var e;
    return void 0 !== (null === (e = this.sourceBuffer) || void 0 === e ? void 0 : e.appendWindowStart);
  }
  seek(e) {
    var n = this;
    return _asyncToGenerator$G(function* () {
      const {duration: d, seekWhenUpdated: h, sourceBuffer: p} = n;
      if (n.resolveSeekPromise(false), Ja.debug("seek to ", e), (e = +e) > d && (Ja.debug("rounding seek time to duration", e, d), e = d), !p) return false;
      if (n.revertSeamlessTransition(), p.updating) return Ja.debug("sourcebuffer updating, deferring seek"), new Promise(d => {
        h && h.resolve(false), n.seekWhenUpdated = {seek: n.seek.bind(n, e), resolve: d};
      });
      n.currentlyLoadingSegmentIndex = void 0, n.updateSegmentToFetch(0, true), n.removeToTime(e), n.timeToTrim = 10 * Math.floor(e / 10);
      const y = n.getSegmentForTime(e);
      0 !== y && (yield n.firstSegmentLoadPromise), Ja.debug("seeking to", e, "segment", y), n.updateSegmentToFetch(y, true);
      const m = new Promise(d => {
        n.seekResolver = {time: e, resolve: d};
      });
      return n.checkSeekBuffered(), m;
    })();
  }
  clearNextManifest() {
    this.revertSeamlessTransition(true), this.playbackTimeline.next = void 0;
  }
  revertSeamlessTransition(e = false) {
    const {playbackTimeline: n, nextSeamlessTransition: d} = this;
    if (!d || !n.previous) return void Ja.debug("no need to revert, no transition");
    this.isAtEndOfStream = e, Ja.debug("reverting seamless transition with discardNextManifest", e), e ? this.clearBufferToEnd(d) : this.clearBuffer(), Ja.debug("abandoning transition to " + this.manifest.mediaItem.title), n.next = e ? void 0 : n.current, n.current = n.previous, n.previous = void 0;
    const h = this.manifest.mediaItem;
    Ja.debug("current item reverted to " + h.title), this.nextSeamlessTransition = void 0, this.duration = h.playbackDuration / 1e3, Ja.debug("reverted duration to " + this.duration), e || (this.currentTimestampOffset = 0, this.timestampOffsetAdjustment = 0, Ja.debug("reverted currentTimestampOffset and timestampOffsetAdjustment to 0")), this.printInfo(), this.segmentIndexToFetch = -1;
  }
  get streamHasEnding() {
    return !this.manifest.mediaItem.isLiveRadioStation;
  }
  stop() {
    this.segmentProcessor.stop(), this.setEndOfStream(), this.remove();
  }
  remove() {
    var e;
    Ja.debug("removing sourceBuffer and mediaSource");
    const {sourceBuffer: n, mediaSource: d} = this;
    null === (e = this.seekResolver) || void 0 === e || e.resolve(false), this.manifest.removeEventListener(Za, this.onManifestParsed);
    const h = this._playableUrl;
    h && (Ja.debug("revoking url", h), window.URL.revokeObjectURL(h)), d.removeEventListener("sourceopen", this.onSourceOpen), n && (n.removeEventListener("updateend", this.updateEndHandler), this.sourceBuffer = void 0);
  }
  onManifestParsed() {
    const e = this.segmentIndexToFetch + 1;
    Ja.debug("manifestParsed, loading segment", e), this.updateSegmentToFetch(e, true);
  }
  updateEndHandler() {
    if (this.kickstartBuffer(), this.clearDeferredRemove()) return;
    if (Ja.debug("update end", this.seekWhenUpdated), this.seekWhenUpdated) {
      Ja.debug("updateEndHandler resolving seekWhenUpdated");
      const {seekWhenUpdated: e} = this;
      return asAsync(e.seek().then(e.resolve)), void (this.seekWhenUpdated = void 0);
    }
    this.checkSeekBuffered();
    const {clip: e, sourceBuffer: n, hasAppendWindowSupport: d} = this;
    if (e && n && !d) {
      const {buffered: d} = n;
      if (this.isTimeBuffered(e.end + 1)) {
        const h = d.end(d.length - 1);
        return Ja.debug("clipping sourcebuffer to", e.end, h), void n.remove(e.end, h);
      }
    }
    if (this.isAtEndOfStream) return Ja.debug("buffer is at end of stream"), this.streamHasEnding && (Ja.debug("isAtEndOfStream, not fetching any more segments"), this.playbackTimeline.next || this.setEndOfStream(), this.transitionToNextManifest()), void (this.isAtEndOfStream = false);
    Ja.debug("updateEndHandler invoking loadSegment"), asAsync(this.loadSegment());
  }
  clearDeferredRemove() {
    var e;
    if (0 === this.deferredRemoves.length) return false;
    const n = this.deferredRemoves.shift();
    return null === (e = this.sourceBuffer) || void 0 === e || e.remove(n.start, n.end), true;
  }
  transitionToNextManifest() {
    var e;
    Ja.debug("beginning transition to next manifest");
    const {playbackTimeline: n, sourceBuffer: d} = this;
    if (!n.next || !d) return void Ja.debug("no next manifest");
    const h = this.endOfBufferTime || this.currentTimestampOffset;
    Ja.debug("setting seamless transition at", h), this.nextSeamlessTransition = h, this.timestampOffsetAdjustment = h, this.playbackTimeline.current.endTime = h, n.previous = n.current, Ja.debug("previous manifest set to", null === (e = n.previous) || void 0 === e ? void 0 : e.manifest.mediaItem.title), n.current = n.next, Ja.debug("current manifest set to", n.current.manifest.mediaItem.title), n.next = void 0, this.updateSegmentToFetch(0, true), this.printInfo();
  }
  updateSegmentToFetch(e, n = false) {
    this.segments.length && e < this.segments.length && e !== this.segmentIndexToFetch && (this.segmentIndexToFetch = e, n && (Ja.debug("updateSegmentToFetch invoking loadSegment"), asAsync(this.loadSegment())));
  }
  loadSegment() {
    var e = this;
    return _asyncToGenerator$G(function* () {
      const n = e.segmentIndexToFetch, d = e.segments[n];
      if (n !== e.currentlyLoadingSegmentIndex) {
        if (d) try {
          Ja.debug("begin loadSegment " + n), e.currentlyLoadingSegmentIndex = n;
          const p = d.load();
          0 === n && (e.firstSegmentLoadPromise = p);
          const y = yield p;
          if (0 !== n && n !== e.segmentIndexToFetch) return void Ja.debug("load segment index to fetch changed, not processing bytes for segment", n);
          e.segmentProcessor.process(d, y), Ja.debug("loadSegment processed: " + n);
          const {sourceBuffer: m, timestampOffsetAdjustment: g} = e;
          if (!m) return;
          try {
            "number" == typeof g && (Ja.debug("adjusting timestampOffset of sourcebuffer to", g), m.timestampOffset = g, e.timestampOffsetAdjustment = void 0), m.appendBuffer(y), e.isFullyBuffered = false, e.isOverBufferLimit = false, Ja.debug("appended to buffer", y.length), e.printBufferTimes(), n === e.segments.length - 1 ? e.isAtEndOfStream = true : n === e.segmentIndexToFetch && (Ja.debug("loadSegment bumping segment index to fetch to ", n + 1), e.updateSegmentToFetch(n + 1));
          } catch (h) {
            "QuotaExceededError" === h.name ? (e.isOverBufferLimit = true, Ja.debug("reached buffer limit")) : Ja.warn("Error appending to source buffer", h);
          }
        } catch (Mr) {
          Ja.error("Error loading segment", Mr), e.dispatcher.publish(Ba, Mr);
        } finally {
          e.currentlyLoadingSegmentIndex = void 0;
        }
      } else Ja.debug(`segment ${n} is currently loading, not loading it again`);
    })();
  }
  setEndOfStream() {
    const {sourceBuffer: e, mediaSource: n} = this;
    e && "ended" !== n.readyState && (e.updating || "open" !== n.readyState ? Ja.error("Could not end of stream (updating, readyState)", e.updating, n.readyState) : (Ja.debug("mediaSource.endOfStream"), n.endOfStream(), this.isFullyBuffered = true));
  }
  removeToTime(e) {
    Ja.debug("removing to time", e), e > 0 && (this.isTimeBuffered(e) || this.isOverBufferLimit) && this.safeSourceBufferRemove(0, e);
  }
  safeSourceBufferRemove(e, n) {
    const {sourceBuffer: d} = this;
    d && (d.updating ? this.deferredRemoves.push({start: e, end: n}) : d.remove(e, n));
  }
  get previousOffset() {
    var e, n;
    return (null === (e = this.playbackTimeline) || void 0 === e || null === (n = e.previous) || void 0 === n ? void 0 : n.endTime) || 0;
  }
  get manifest() {
    var e;
    return null === (e = this.playbackTimeline.current) || void 0 === e ? void 0 : e.manifest;
  }
  checkSeekBuffered() {
    const {seekResolver: e, currentTimestampOffset: n} = this;
    if (!e) return;
    const {time: d} = e, h = d + n, p = this.isTimeBuffered(h);
    Ja.debug("resolving seek for time, adjustedTime, isBuffered", d, h, p), this.printBufferTimes(), p && (Ja.debug("resolving seek to true for time:", h), this.element.currentTime = h, this.resolveSeekPromise(true));
  }
  resolveSeekPromise(e) {
    this.seekResolver && (this.seekResolver.resolve(e), this.seekResolver = void 0);
  }
  get endOfBufferTime() {
    var e;
    const n = null === (e = this.sourceBuffer) || void 0 === e ? void 0 : e.buffered;
    return !(!n || !n.length) && n.end(n.length - 1);
  }
  isTimeBuffered(e) {
    var n;
    const d = null === (n = this.sourceBuffer) || void 0 === n ? void 0 : n.buffered;
    if (!d) return false;
    for (let h = 0; h < d.length; h++) if (Ja.debug("isTimeBuffered", d.start(h), e, d.end(h)), e >= d.start(h) && e <= d.end(h)) return true;
    return false;
  }
  clearBufferToEnd(e) {
    const {sourceBuffer: n} = this;
    if (!n || !n.buffered) return;
    const d = n.buffered.end(n.buffered.length - 1);
    this.safeSourceBufferRemove(e, d);
  }
  clearBuffer() {
    const {sourceBuffer: e} = this;
    if (!e || !e.buffered) return;
    const n = e.buffered;
    for (let d = 0; d < n.length; d++) this.safeSourceBufferRemove(n.start(d), n.end(d));
  }
  get bufferTimesString() {
    var e;
    const n = null === (e = this.sourceBuffer) || void 0 === e ? void 0 : e.buffered;
    if (!n) return "";
    const d = [];
    for (let h = 0; h < n.length; h++) d.push(`start ${n.start(h)} end: ${n.end(h)}`);
    return d.join(",");
  }
  printBufferTimes() {
    Xa && Ja.debug("buffer times", this.bufferTimesString);
  }
  getSegmentForTime(e) {
    return Math.floor(e / 10) + 1;
  }
  kickstartBuffer() {
    const {hasKickstarted: e, element: n, clip: d} = this, {buffered: h} = n;
    e || (this.manifest.mediaItem.isSong ? d && this.isTimeBuffered(d.start) && (n.currentTime = d.start, this.hasKickstarted = true) : h.length && (n.currentTime = h.start(0), this.hasKickstarted = true));
  }
  printInfo() {
    var e, n;
    const {playbackTimeline: d} = this;
    Ja.info("---- Buffer Info ----"), Ja.info("currently buffering item", d.current.manifest.mediaItem.title), Ja.info("next item to buffer", null === (e = d.next) || void 0 === e ? void 0 : e.manifest.mediaItem.title), Ja.info("previously buffered item", null === (n = d.previous) || void 0 === n ? void 0 : n.manifest.mediaItem.title), Ja.info("currentTimestampOffset", this.currentTimestampOffset), Ja.info("currentTime", this.currentTime), Ja.info("duration", this.duration), Ja.info("nextSeamlessTransition", this.nextSeamlessTransition), Ja.info("timestampOffsetAdjustment", this.timestampOffsetAdjustment), Ja.info("buffered times", this.bufferTimesString), Ja.info("isAtEndOfStream", this.isAtEndOfStream), Ja.info("isFullyBuffered", this.isFullyBuffered), Ja.info("segmentIndexToFetch", this.segmentIndexToFetch), Ja.info("segments.length", this.segments.length), Ja.info("---- End Buffer Info ----");
  }
  constructor({dispatcher: e, element: n, manifest: d, currentTime: h, duration: p, clip: y}) {
    this.firstSegmentLoadPromise = Promise.resolve(), this.hasKickstarted = false, this.segmentIndexToFetch = -1, this.timeToTrim = 10, this.isAtEndOfStream = false, this.isFullyBuffered = false, this.deferredRemoves = [], this.currentTimestampOffset = 0, this.dispatcher = e, this.clip = y, this.element = n, this.mediaSource = new MediaSource, this.mediaSource.addEventListener("sourceopen", this.onSourceOpen), this.segmentProcessor = new SegmentProcessor(d.mediaItem, n, e), this.playbackTimeline = {current: {manifest: d}}, d.addEventListener(Za, this.onManifestParsed), this._currentTime = h || 0, this.duration = p, window.mseBuffer = this;
  }
}
