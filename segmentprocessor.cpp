#include "segmentprocessor.h"

SegmentProcessor::SegmentProcessor()
{

}
class SegmentProcessor {
  process(e, n) {
    const {_item: d} = this;
    try {
      d.isLiveRadioStation ? this._processLiveRadioSegment(n) : d.hasOffersHlsUrl && this._processHlsOffersSegment(e, n);
    } catch (Mr) {
      Ct.error("Error processing segment", Mr);
    }
  }
  stop() {
    this._timedMetadataManager.stop();
  }
  _processHlsOffersSegment(e, n) {
    e.isInitSegment && rewriteDefaultKid(n);
  }
  _processLiveRadioSegment(e) {
    this._timedMetadataManager.processEmsgs(e);
  }
  constructor(e, n, d) {
    this._item = e, this._timedMetadataManager = new TimedMetadataManager(() => n.currentTime, e => {
      d.publish(Ga, e.timedMetadata);
    });
  }
}
