var callbacks = {};
var nextId = 0;

function getNextId() {
  return nextId++;
}

extension.setMessageListener(function(json) {
  var ext = JSON.parse(json);
  var callback = callbacks[id];

  if (typeof(callback) === 'function') {
    callback(ext.err, JSON.parse(ext.response));
    delete ext.id;
    delete callbacks[ext.id];
  } else {
    console.error('invalid callback id: ' + ext.id);
  }
});

exports.getPath = function(callback) {
  var request = {
    id: getNextId(),
    message: 'get-path'
  };

  callbacks[request.id] = callback;
  extension.postMessage(JSON.stringify(request));
};
