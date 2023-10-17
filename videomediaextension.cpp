#include "videomediaextension.h"

VideoMediaExtension::VideoMediaExtension()
{

}
class VideoMediaExtension extends MediaExtension {
  destroy(e) {
    var n;
    null === (n = this._session) || void 0 === n || n.stopLicenseSession(), super.destroy(e);
  }
}
