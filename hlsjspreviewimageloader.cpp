#include "hlsjspreviewimageloader.h"

HlsJsPreviewImageLoader::HlsJsPreviewImageLoader()
{

}
class HlsJsPreviewImageLoader {
  loadPreviewImage(e) {
    return this.lastPosition === e || (this.lastPosition = e, this.lastPromise = new Promise((n, d) => {
      this.hls.loadImageIframeData$(e).subscribe(e => {
        const {data: d} = e, h = new Blob([d], {type: "image/jpeg"});
        n(h);
      });
    })), this.lastPromise;
  }
  constructor(e) {
    this.hls = e;
  }
}
