module.exports = [

	{
		"type": "heading",
		"defaultValue": "NCAA FBS Face Configuration"
	},
	{
		"type": "text",
		"defaultValue": "Show your allegiance."
	},
	{
		"type": "section",
		"items": [
			{
				"type": "heading",
				"defaultValue": "Animations"
			},
			{
				"type": "select",
				"messageKey": "ANIMATION",
				"defaultValue": "2",
				"label": "Animations",
				"options": [
					{ 
						"label": "", 
						"value": "" 
					},
					{ 
						"label": "On",
						"value": 0 
					},
					{ 
						"label": "Off",
						"value": 1
					},
					{ 
						"label": "Auto",
						"value": 2 
					}
				]
			},
			{
				"type": "slider",
				"messageKey": "AUTORANGE",
				"defaultValue": 20,
				"label": "Auto Animations Off Precent",
				"min": 5,
				"max": 95,
				"step": 5
			},
			{
				"type": "toggle",
				"messageKey": "QUIET",
				"label": "Quiet Time",
				"defaultValue": true
			},
			{
				"type": "input",
				"messageKey": "QSTART",
				"defaultValue": "",
				"label": "Quiet Time Start",
				"attributes": {
					"placeholder": "eg: 10:00 PM",
					"limit": 10,
					"type": "time"
				}
			},
			{
				"type": "input",
				"messageKey": "QEND",
				"defaultValue": "",
				"label": "Quiet Time End",
				"attributes": {
					"placeholder": "eg: 7:00 AM",
					"limit": 10,
					"type": "time"
				}
			}
		]
	},
	{
		"type": "section",
		"items": [
			{
				"type": "heading",
				"defaultValue": "Bluetooth"
			},
			{
				"type": "select",
				"messageKey": "DISCONNECT",
				"defaultValue": "3",
				"label": "Disconnect Vibration",
				"options": [
					{ 
						"label": "", 
						"value": "" 
					},
					{ 
						"label": "Off",
						"value": 0 
					},
					{ 
						"label": "Short",
						"value": 1
					},
					{ 
						"label": "Long",
						"value": 2 
					},
					{ 
						"label": "Double",
						"value": 3 
					}
				]
			},
			{
				"type": "select",
				"messageKey": "RECONNECT",
				"defaultValue": "1",
				"label": "Reconnect Vibration",
				"options": [
					{ 
						"label": "", 
						"value": "" 
					},
					{ 
						"label": "Off",
						"value": 0 
					},
					{ 
						"label": "Short",
						"value": 1
					},
					{ 
						"label": "Long",
						"value": 2 
					},
					{ 
						"label": "Double",
						"value": 3 
					}
				]
			}
		]
	},
	{
		"type": "section",
		"items": [
			{
				"type": "heading",
				"defaultValue": "Display"
			},
			{
				"type": "radiogroup",
				"messageKey": "WINDOW",
				"defaultValue": "0",
				"label": "What would you like your main display to be?",
				"options": [
					{ 
						"label": "Favorite Team", 
						"value": 0 
					},
					{ 
						"label": "Team You Want to Beat", 
						"value": 1
					}
				]
			},
			{
				"type": "select",
				"messageKey": "TEAM",
				"defaultValue": "0",
				"label": "Favorite Team",
				"options": [
					{ 
						"label": "", 
						"value": "" 
					},
					{ 
						"label": "Off",
						"value": 0 
					},
					{ 
						"label": "Short",
						"value": 1
					},
					{ 
						"label": "Long",
						"value": 2 
					},
					{ 
						"label": "Double",
						"value": 3 
					}
				]
			},
			{
				"type": "select",
				"messageKey": "BADTEAM",
				"defaultValue": "0",
				"label": "Team You Want to Beat",
				"options": [
					{ 
						"label": "", 
						"value": "" 
					},
					{ 
						"label": "Off",
						"value": 0 
					},
					{ 
						"label": "Short",
						"value": 1
					},
					{ 
						"label": "Long",
						"value": 2 
					},
					{ 
						"label": "Double",
						"value": 3 
					}
				]
			}
		]
	},
	{
		"type": "section",
		"items": [
			{
				"type": "heading",
				"defaultValue": "Countdown *PREMIUM FEATURE*"
			},
			{
				"type": "toggle",
				"messageKey": "COUNTDOWN",
				"label": "Countdown to Gametime?",
				"defaultValue": false
			},
			{
				"type": "radiogroup",
				"messageKey": "COUNTDOWNDEFAULT",
				"defaultValue": "1",
				"label": "Gametime",
				"options": [
					{ 
						"label": "Custom", 
						"value": 0 
					},
					{ 
						"label": "Default (Saturday at Noon EST)", 
						"value": 1
					}
				]
			},
			{
				"type": "input",
				"messageKey": "GAMETIME",
				"defaultValue": "",
				"label": "Gametime",
				"attributes": {
					"placeholder": "eg: 8:00 PM",
					"limit": 10,
					"type": "time"
				}
			},
			{
				"type": "input",
				"messageKey": "GAMEDAY",
				"defaultValue": "",
				"label": "Game Date",
				"attributes": {
					"placeholder": "eg: 9/1/2016",
					"limit": 15,
					"type": "date"
				}
			},
			{
				"type": "radiogroup",
				"messageKey": "COUNTDOWNANI",
				"defaultValue": "1",
				"label": "Gametime",
				"options": [
					{ 
						"label": "Main Window and Animation", 
						"value": 0 
					},
					{ 
						"label": "On Animation only - not Main Window", 
						"value": 1
					},
					{ 
						"label": "On Main Window only - not Animation", 
						"value": 2
					}
				]
			}
		]
	},
	{
		"type": "section",
		"items": [
			{
				"type": "heading",
				"defaultValue": "Health Data *PREMIUM FEATURE*"
			},
			{
				"type": "toggle",
				"messageKey": "STEPS",
				"label": "Step Count",
				"defaultValue": false
			},
			{
				"type": "toggle",
				"messageKey": "TD",
				"label": "Goal Guide",
				"defaultValue": false
			}
		]
	},
	{
		"type": "section",
		"items": [
			{
				"type": "heading",
				"defaultValue": "Developer"
			},
			{
				"type": "radiogroup",
				"messageKey": "VERSION",
				"defaultValue": "300",
				"label": "Version",
				"options": [
					{ 
						"label": "3.00", 
						"value": 300 
					}
				]
			}
		]
	},
  {
    "type": "submit",
    "defaultValue": "Save"
  }

];