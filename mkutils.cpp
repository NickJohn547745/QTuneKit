#include "mkutils.h"

JObject mergeObjects(QList<JObject> jObjs) {
    JObject result = JObject();
    foreach (JObject jObj, jObjs) {
        foreach (QString key, jObj.keys()) {
            result[key] = jObj[key];
        }
    }
    return result;
}
