var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
  }
  function onOpen(event) {
    console.log('Connection opened');
initButtonUp();
    initButtonLeft();
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  function onLoad(event) {
    initWebSocket();
  }
  function initButtonUp() {
    document.getElementById('upButton').addEventListener('click', toggleUp);
  }
  function toggleUp(){
    websocket.send('toggleUp');
  }
  function initButtonLeft() {
    document.getElementById('leftButton').addEventListener('click', toggleLeft);
  }
  function toggleLeft(){
    websocket.send('toggleLeft');
  }