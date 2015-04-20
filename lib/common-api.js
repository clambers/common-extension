extension.setMessageListener(function(msg) {});

exports.getPath = function(msg) {
  return extension.internal.sendSyncMessage(msg);
};
