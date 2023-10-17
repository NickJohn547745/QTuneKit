#include "mkerror.h"

MKError::MKError(JObject e, QString n)
{
    errorCode = "UNKNOWN_ERROR";

    if (!e.isEmpty() && errorList.contains(e)) {
        name = e;
        errorCode = e;
        message = !n.isEmpty() ? n : e;
        description = !n.isEmpty() ? n : e;
    } else if (!n.isEmpty()) {
        name = !e.isEmpty() ? e : "UNKNOWN_ERROR";
        errorCode = !e.isEmpty() ? e : "UNKNOWN_ERROR";
        message = n;
        description = n;
    } else {
        name = "UNKNOWN_ERROR";
        errorCode = "UNKNOWN_ERROR";
        message = e;
        description = e;
    }
}

void MKError::preInitialization() {
    httpErrorCodes = {
        {400, "REQUEST_ERROR"},
        {401, "UNAUTHORIZED_ERROR"},
        {403, "ACCESS_DENIED"},
        {404, "NOT_FOUND"},
        {405, "METHOD_NOT_ALLOWED"},
        {413, "PAYLOAD_TOO_LARGE"},
        {414, "URI_TOO_LONG"},
        {429, "QUOTA_EXCEEDED"},
        {500, "SERVER_ERROR"},
        {501, "NOT_IMPLEMENTED"},
        {503, "SERVICE_UNAVAILABLE"}
    };
    appErrorCodes = {
        {-1004, "DEVICE_LIMIT"},
        {-1017, "GEO_BLOCK"},
        {1010, httpErrorCodes[404]},
        {2002, "AUTHORIZATION_ERROR"},
        {2034, "TOKEN_EXPIRED"},
        {3059, "DEVICE_LIMIT"},
        {3063, "SUBSCRIPTION_ERROR"},
        {3076, "CONTENT_UNAVAILABLE"},
        {3082, "CONTENT_RESTRICTED"},
        {3084, "STREAM_UPSELL"},
        {5002, httpErrorCodes[500]},
        {180202, "PLAYREADY_CBC_ENCRYPTION_ERROR"},
        {190121, "WIDEVINE_CDM_EXPIRED"}
    };
    errorList = {
        "CONTENT_EQUIVALENT",
        "CONTENT_UNAVAILABLE",
        "CONTENT_UNSUPPORTED",
        "SERVER_ERROR",
        "SUBSCRIPTION_ERROR",
        "UNSUPPORTED_ERROR",
        "USER_INTERACTION_REQUIRED"
    };

}

void MKError::postInitialization() {
    errorMap["ACCESS_DENIED"] = httpErrorCodes[403];
    errorMap["AGE_VERIFICATION"] = "AGE_VERIFICATION";
    errorMap["AUTHORIZATION_ERROR"] = appErrorCodes[2002];
    errorMap["BUFFER_STALLED_ERROR"] = "BUFFER_STALLED_ERROR";
    errorMap["CONFIGURATION_ERROR"] = "CONFIGURATION_ERROR";
    errorMap["CONTENT_EQUIVALENT"] = "CONTENT_EQUIVALENT";
    errorMap["CONTENT_RESTRICTED"] = appErrorCodes[3082];
    errorMap["CONTENT_UNAVAILABLE"] = appErrorCodes[3076];
    errorMap["CONTENT_UNSUPPORTED"] = "CONTENT_UNSUPPORTED";
    errorMap["DEVICE_LIMIT"] = appErrorCodes[3059];
    errorMap["GEO_BLOCK"] = appErrorCodes[-1017];
    errorMap["INVALID_ARGUMENTS"] = "INVALID_ARGUMENTS";
    errorMap["PLAYREADY_CBC_ENCRYPTION_ERROR"] = "PLAYREADY_CBC_ENCRYPTION_ERROR";
    errorMap["MEDIA_CERTIFICATE"] = "MEDIA_CERTIFICATE";
    errorMap["MEDIA_DESCRIPTOR"] = "MEDIA_DESCRIPTOR";
    errorMap["MEDIA_LICENSE"] = "MEDIA_LICENSE";
    errorMap["MEDIA_KEY"] = "MEDIA_KEY";
    errorMap["MEDIA_PLAYBACK"] = "MEDIA_PLAYBACK";
    errorMap["MEDIA_SESSION"] = "MEDIA_SESSION";
    errorMap["NETWORK_ERROR"] = "NETWORK_ERROR";
    errorMap["NOT_FOUND"] = appErrorCodes[1010];
    errorMap["PARSE_ERROR"] = "PARSE_ERROR";
    errorMap["PLAY_ACTIVITY"] = "PLAY_ACTIVITY";
    errorMap["QUOTA_EXCEEDED"] = httpErrorCodes[429];
    errorMap["REQUEST_ERROR"] = httpErrorCodes[400];
    errorMap["SERVER_ERROR"] = appErrorCodes[5002];
    errorMap["SERVICE_UNAVAILABLE"] = httpErrorCodes[503];
    errorMap["STREAM_UPSELL"] = appErrorCodes[3084];
    errorMap["SUBSCRIPTION_ERROR"] = appErrorCodes[3063];
    errorMap["TOKEN_EXPIRED"] = appErrorCodes[2034];
    errorMap["UNAUTHORIZED_ERROR"] = httpErrorCodes[401];
    errorMap["UNKNOWN_ERROR"] = "UNKNOWN_ERROR";
    errorMap["UNSUPPORTED_ERROR"] = "UNSUPPORTED_ERROR";
    errorMap["USER_INTERACTION_REQUIRED"] = "USER_INTERACTION_REQUIRED";
    errorMap["INTERNAL_ERROR"] = "INTERNAL_ERROR";
    errorMap["OUTPUT_RESTRICTED"] = "OUTPUT_RESTRICTED";
    errorMap["WIDEVINE_CDM_EXPIRED"] = "WIDEVINE_CDM_EXPIRED";
}

MKError MKError::playActivityError(QString e) {
    return MKError("PLAY_ACTIVITY", e);
}

MKError MKError::parseError(QString e) {
    return MKError("PARSE_ERROR", e);
}

MKError MKError::responseError(QString e) {
    const {
        status: n,
        statusText: d
    } = e




    h = MKError(httpErrorCodes[n] || "NETWORK_ERROR", d || "" + n);
    return h.data = e, h;
}

MKError MKError::serverError(QString e, n = "UNKNOWN_ERROR") {

    let {
        status: d,
        dialog: h,
        failureType: p,
        customerMessage: y,
        errorMessage: m,
        message: g
    } = e;

    // Check if 'h' exists and has properties to determine the message 'g'
    if (h) {
        if (h.message) {
            g = h.message;
        } else if (h.customerMessage) {
            g = h.customerMessage;
        } else if (h.errorMessage) {
            g = h.errorMessage;
        }
        h.message = g;
    }

    // Determine the error code 'b' based on 'p', 'd', or a default value 'n'
    const QString b = (appErrorCodes.contains(p)) ? (p) : ((appErrorCodes.contains(d)) ? (d) : (n));

    // Create a new instance 'T' based on the error code and message
    const MKError T = MKError(b, g || y || m);

    // Modify 'h.okButtonAction.url' if certain conditions are met
    if ("STREAM_UPSELL" === b && h && h.okButtonAction && h.okButtonAction.url) {
        h.okButtonAction.url = h.okButtonAction.url.replace(/\&(?:challenge|key-system|uri|user-initiated)=[^\&]+/gim, "");
    }

    // Assign the dialog 'h' to the instance 'T'
    T.dialog = h;

    // Return the instance 'T'
    return T;

    /*let {status: d, dialog: h, failureType: p, customerMessage: y, errorMessage: m, message: g} = e;
        h && (g = h.message || h.customerMessage || h.errorMessage, h.message = g);
        const b = appErrorCodes[p] || appErrorCodes[d] || n, T = new this(b, g || y || m);
    return "STREAM_UPSELL" === b && h && h.okButtonAction && h.okButtonAction.url && (h.okButtonAction.url = h.okButtonAction.url.replace(/\&(?:challenge|key-system|uri|user-initiated)=[^\&]+/gim, "")), T.dialog = h, T;
    */
}

MKError MKError::internalError(QString e) {
    return MKError(errorMap["INTERNAL_ERROR"], e);
}

        /*
    class MKError extends Error {
    static playActivityError(e) {
      return new this("PLAY_ACTIVITY", e);
    }
    static parseError(e) {
      return new this("PARSE_ERROR", e);
    }
    static responseError(e) {
      const {status: n, statusText: d} = e, h = new this(b[n] || "NETWORK_ERROR", d || "" + n);
      return h.data = e, h;
    }
    static serverError(e, n = "UNKNOWN_ERROR") {
      let {status: d, dialog: h, failureType: p, customerMessage: y, errorMessage: m, message: g} = e;
      h && (g = h.message || h.customerMessage || h.errorMessage, h.message = g);
      const b = _[p] || _[d] || n, T = new this(b, g || y || m);
      return "STREAM_UPSELL" === b && h && h.okButtonAction && h.okButtonAction.url && (h.okButtonAction.url = h.okButtonAction.url.replace(/\&(?:challenge|key-system|uri|user-initiated)=[^\&]+/gim, "")), T.dialog = h, T;
    }
    static internalError(e) {
      return new this(MKError.INTERNAL_ERROR, e);
    }
    constructor(e, n) {
      super(), this.errorCode = "UNKNOWN_ERROR", e && T.has(e) ? (this.name = this.errorCode = e, this.message = this.description = n || e) : n || "string" != typeof e ? (this.name = this.errorCode = e || "UNKNOWN_ERROR", n && (this.message = this.description = n)) : (this.name = this.errorCode = "UNKNOWN_ERROR", this.message = this.description = e), Error.captureStackTrace && Error.captureStackTrace(this, MKError);
    }
  }

