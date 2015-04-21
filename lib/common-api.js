var commonListener = null;

extension.setMessageListener(function(msg) {
  if (commonListener instanceof Function) {
    commonListener(msg);
  }
});

exports.getVersion = function(cb) {
  commonListener = cb;
  extension.postMessage('get-version');
};

exports.getPath = function(cb) {
  commonListener = cb;
  extension.postMessage('get-path');
};

exports.forceError = function(cb) {
  commonListener = cb;
  extension.postMessage('foobar');
};
