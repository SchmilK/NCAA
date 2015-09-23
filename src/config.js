Pebble.addEventListener("ready",
  function(e) {
    console.log("PebbleKit JS ready!");
  }
);

Pebble.addEventListener("showConfiguration",
  function(e) {
    //Load the remote config page
    Pebble.openURL("http://kflinderman.github.io/NCAA/index2");
  }
);

Pebble.addEventListener("webviewclosed", function(e){
	console.log("Configuration closed");
	console.log("Response = " + e.response.length + "   " + e.response);
	if (e.response !== undefined && e.response !== '' && e.response !== 'CANCELLED') {
		console.log("User hit save");
		values = JSON.parse(decodeURIComponent(e.response));
		console.log("stringified options: " + JSON.stringify((values)));
		Pebble.sendAppMessage(
			values
		);
		console.log("Sending...");
	}
});