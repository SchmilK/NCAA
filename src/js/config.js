module.exports = [

	{
		"type": "heading",
		"defaultValue": "NCAA FBS Face Configuration"
	},
	{
		"type": "text",
		"defaultValue": "Show your passion."
	},
	{
		"type": "section",
		"capabilities": ["NOT_PLATFORM_APLITE"],
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
				"defaultValue": false
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
				"capabilities": ["NOT_PLATFORM_APLITE"],
				"messageKey": "TEAM",
				"defaultValue": "0",
				"label": "Favorite Team",
				"options": [
					{ 
						"label": "Random (Changes Sundays) *Premium Feature*", 
						"value": 143 
					},
					{
						"label": "AAC",
						"value": [
							{ 
								"label": "AAC Logo",
								"value": 129 
							},
							{ 
								"label": "UCF",
								"value": 17 
							},
							{ 
								"label": "Cincinnati",
								"value": 19 
							},
							{ 
								"label": "UConn",
								"value": 23 
							},
							{ 
								"label": "ECU",
								"value": 25 
							},
							{ 
								"label": "Houston",
								"value": 37 
							},
							{ 
								"label": "Memphis",
								"value": 55 
							},
							{ 
								"label": "USF",
								"value": 92 
							},
							{ 
								"label": "SMU",
								"value": 90 
							},
							{ 
								"label": "Temple",
								"value": 98 
							},
							{ 
								"label": "Tulane",
								"value": 107
							},
							{ 
								"label": "Tulsa",
								"value": 108 
							}
						]
					}, 
					{
						"label": "ACC",
						"value": [
							{ 
								"label": "ACC Logo",
								"value": 130 
							},
							{ 
								"label": "Boston College",
								"value": 12 
							},
							{ 
								"label": "Clemson",
								"value": 20 
							},
							{ 
								"label": "Duke",
								"value": 24 
							},
							{ 
								"label": "FSU",
								"value": 30 
							},
							{ 
								"label": "Georgia Tech",
								"value": 35 
							},
							{ 
								"label": "Louisville",
								"value": 50 
							},
							{ 
								"label": "Miami",
								"value": 56 
							},
							{ 
								"label": "UNC",
								"value": 70 
							},
							{ 
								"label": "NC State",
								"value": 71 
							},
							{ 
								"label": "Pitt",
								"value": 84 
							},
							{ 
								"label": "Syracuse",
								"value": 96
							},
							{ 
								"label": "UVA",
								"value": 116 
							},
							{ 
								"label": "Virginia Tech",
								"value": 117
							},
							{ 
								"label": "Wake",
								"value": 118
							}
						]
					}, 
					{
						"label": "B1G",
						"value": [
							{ 
								"label": "B1G Logo",
								"value": 131 
							},
							{ 
								"label": "Illinois",
								"value": 39 
							},
							{ 
								"label": "Indiana",
								"value": 40 
							},
							{ 
								"label": "Iowa",
								"value": 41 
							},
							{ 
								"label": "Maryland",
								"value": 53 
							},
							{ 
								"label": "Michigan",
								"value": 58 
							},
							{ 
								"label": "Minnesota",
								"value": 61 
							},
							{ 
								"label": "Nebraska",
								"value": 66 
							},
							{ 
								"label": "Northwestern",
								"value": 74 
							},
							{ 
								"label": "Ohio State",
								"value": 76 
							},
							{ 
								"label": "Penn State",
								"value": 83 
							},
							{ 
								"label": "Purdue",
								"value": 85
							},
							{ 
								"label": "Rutgers",
								"value": 87 
							},
							{ 
								"label": "Wisconsin",
								"value": 122
							}
						]
					}, 
					{
						"label": "Big 12",
						"value": [
							{ 
								"label": "Big 12 Logo",
								"value": 132 
							},
							{ 
								"label": "Baylor",
								"value": 10 
							},
							{ 
								"label": "Iowa State",
								"value": 42 
							},
							{ 
								"label": "Kansas",
								"value": 43 
							},
							{ 
								"label": "Kansas State",
								"value": 44 
							},
							{ 
								"label": "Oklahoma",
								"value": 78 
							},
							{ 
								"label": "Oklahoma State",
								"value": 79 
							},
							{ 
								"label": "Texas",
								"value": 100 
							},
							{ 
								"label": "TCU",
								"value": 97 
							},
							{ 
								"label": "Texas Tech",
								"value": 103 
							},
							{ 
								"label": "WVU",
								"value": 124 
							}
						]
					}, 
					{
						"label": "C-USA",
						"value": [
							{ 
								"label": "C-USA Logo",
								"value": 133
							},
							{ 
								"label": "UAB",
								"value": 126 
							},
							{ 
								"label": "FAU",
								"value": 28 
							},
							{ 
								"label": "FIU",
								"value": 29 
							},
							{ 
								"label": "Louisiana Tech",
								"value": 47 
							},
							{ 
								"label": "Marshall",
								"value": 52 
							},
							{ 
								"label": "Middle Tennessee State",
								"value": 60 
							},
							{ 
								"label": "UNC-Charlotte",
								"value": 110 
							},
							{ 
								"label": "North Texas",
								"value": 72 
							},
							{ 
								"label": "ODU",
								"value": 80 
							},
							{ 
								"label": "Rice",
								"value": 86 
							},
							{ 
								"label": "Southern Miss",
								"value": 94 
							},
							{ 
								"label": "UTEP",
								"value": 114 
							},
							{ 
								"label": "UTSA",
								"value": 104 
							},
							{ 
								"label": "WKU",
								"value": 123 
							}
						]
					}, 
					{
						"label": "Independent",
						"value": [
							{ 
								"label": "Army",
								"value": 7
							},
							{ 
								"label": "Navy",
								"value": 65 
							},
							{ 
								"label": "Notre Dame",
								"value": 75 
							},
							{ 
								"label": "BYU",
								"value": 14 
							}
						]
					}, 
					{
						"label": "MAC",
						"value": [
							{ 
								"label": "MAC Logo",
								"value": 134
							},
							{ 
								"label": "Akron",
								"value": 2 
							},
							{ 
								"label": "Ball State",
								"value": 9 
							},
							{ 
								"label": "Bowling Green",
								"value": 13 
							},
							{ 
								"label": "Buffalo",
								"value": 15 
							},
							{ 
								"label": "Central Michigan",
								"value": 18 
							},
							{ 
								"label": "Eastern Michigan",
								"value": 26 
							},
							{ 
								"label": "Kent State",
								"value": 45 
							},
							{ 
								"label": "UMass",
								"value": 54 
							},
							{ 
								"label": "Miami (OH)",
								"value": 57 
							},
							{ 
								"label": "NIU",
								"value": 73 
							},
							{ 
								"label": "Ohio",
								"value": 77 
							},
							{ 
								"label": "Toledo",
								"value": 105 
							},
							{ 
								"label": "Western Michigan",
								"value": 121 
							}
						]
					}, 
					{
						"label": "MWC",
						"value": [
							{ 
								"label": "MWC Logo",
								"value": 135
							},
							{ 
								"label": "Air Force",
								"value": 1 
							},
							{ 
								"label": "Boise State",
								"value": 11 
							},
							{ 
								"label": "Fresno State",
								"value": 31 
							},
							{ 
								"label": "Colorado State",
								"value": 22 
							},
							{ 
								"label": "Hawaii",
								"value": 36 
							},
							{ 
								"label": "Nevada",
								"value": 67 
							},
							{ 
								"label": "UNLV",
								"value": 111 
							},
							{ 
								"label": "New Mexico",
								"value": 68 
							},
							{ 
								"label": "San Diego State",
								"value": 88 
							},
							{ 
								"label": "San Jose State",
								"value": 89 
							},
							{ 
								"label": "Utah State",
								"value": 113 
							},
							{ 
								"label": "Whyoming",
								"value": 125 
							}
						]
					}, 
					{
						"label": "Pac-12",
						"value": [
							{ 
								"label": "Pac-12 Logo",
								"value": 136
							},
							{ 
								"label": "Arizona",
								"value": 5 
							},
							{ 
								"label": "Arizona State",
								"value": 6 
							},
							{ 
								"label": "Cal",
								"value": 16 
							},
							{ 
								"label": "UCLA",
								"value": 109 
							},
							{ 
								"label": "Colorado",
								"value": 21 
							},
							{ 
								"label": "Oregon",
								"value": 81 
							},
							{ 
								"label": "Oregon State",
								"value": 82 
							},
							{ 
								"label": "Southern Cal",
								"value": 93 
							},
							{ 
								"label": "Stanford",
								"value": 95 
							},
							{ 
								"label": "Utah",
								"value": 112 
							},
							{ 
								"label": "Washington",
								"value": 119 
							},
							{ 
								"label": "Washington State",
								"value": 120 
							}
						]
					}, 
					{
						"label": "SEC",
						"value": [
							{ 
								"label": "SEC Logo",
								"value": 137
							},
							{ 
								"label": "Alabama",
								"value": 3 
							},
							{ 
								"label": "Arkansas",
								"value": 140 
							},
							{ 
								"label": "Auburn",
								"value": 8 
							},
							{ 
								"label": "Florida",
								"value": 27 
							},
							{ 
								"label": "Georgia",
								"value": 32 
							},
							{ 
								"label": "Kentucky",
								"value": 46 
							},
							{ 
								"label": "LSU",
								"value": 51 
							},
							{ 
								"label": "Ole Miss",
								"value": 62 
							},
							{ 
								"label": "Mississippi State",
								"value": 63 
							},
							{ 
								"label": "Missouri",
								"value": 64 
							},
							{ 
								"label": "South Carolina",
								"value": 0 
							},
							{ 
								"label": "Tennessee",
								"value": 99 
							},
							{ 
								"label": "Texas A&M",
								"value": 101 
							},
							{ 
								"label": "Vanderbilt",
								"value": 115 
							}
						]
					}, 
					{
						"label": "Sun Belt",
						"value": [
							{ 
								"label": "Sun Belt Logo",
								"value": 138
							},
							{ 
								"label": "App State",
								"value": 4 
							},
							{ 
								"label": "Arkansas State",
								"value": 141 
							},
							{ 
								"label": "Georgia Southern",
								"value": 33 
							},
							{ 
								"label": "Georgia State",
								"value": 34 
							},
							{ 
								"label": "Idaho",
								"value": 38 
							},
							{ 
								"label": "UL-Lafayette",
								"value": 48 
							},
							{ 
								"label": "UL_Monroe",
								"value": 49 
							},
							{ 
								"label": "New Mexico State",
								"value": 69 
							},
							{ 
								"label": "South Alabama",
								"value": 91 
							},
							{ 
								"label": "Texas State",
								"value": 102 
							},
							{ 
								"label": "Troy",
								"value": 106 
							}
						]
					}, 
					{
						"label": "Other",
						"value": [
							{ 
								"label": "NCAA Logo",
								"value": 127
							},
							{ 
								"label": "CFB Playoff Logo",
								"value": 128 
							},
							{ 
								"label": "Team Chaos",
								"value": 139 
							},
							{ 
								"label": "Team Meteor",
								"value": 142 
							}
						]
					}
				]
			},
			{
				"type": "select",
				"capabilities": ["NOT_PLATFORM_APLITE"],
				"messageKey": "BADTEAM",
				"defaultValue": "20",
				"label": "Team You Want to Beat",
				"options": [
					{ 
						"label": "Random (Changes Sundays) *Premium Feature*", 
						"value": 143 
					},
					{
						"label": "AAC",
						"value": [
							{ 
								"label": "AAC Logo",
								"value": 129 
							},
							{ 
								"label": "UCF",
								"value": 17 
							},
							{ 
								"label": "Cincinnati",
								"value": 19 
							},
							{ 
								"label": "UConn",
								"value": 23 
							},
							{ 
								"label": "ECU",
								"value": 25 
							},
							{ 
								"label": "Houston",
								"value": 37 
							},
							{ 
								"label": "Memphis",
								"value": 55 
							},
							{ 
								"label": "USF",
								"value": 92 
							},
							{ 
								"label": "SMU",
								"value": 90 
							},
							{ 
								"label": "Temple",
								"value": 98 
							},
							{ 
								"label": "Tulane",
								"value": 107
							},
							{ 
								"label": "Tulsa",
								"value": 108 
							}
						]
					}, 
					{
						"label": "ACC",
						"value": [
							{ 
								"label": "ACC Logo",
								"value": 130 
							},
							{ 
								"label": "Boston College",
								"value": 12 
							},
							{ 
								"label": "Clemson",
								"value": 20 
							},
							{ 
								"label": "Duke",
								"value": 24 
							},
							{ 
								"label": "FSU",
								"value": 30 
							},
							{ 
								"label": "Georgia Tech",
								"value": 35 
							},
							{ 
								"label": "Louisville",
								"value": 50 
							},
							{ 
								"label": "Miami",
								"value": 56 
							},
							{ 
								"label": "UNC",
								"value": 70 
							},
							{ 
								"label": "NC State",
								"value": 71 
							},
							{ 
								"label": "Pitt",
								"value": 84 
							},
							{ 
								"label": "Syracuse",
								"value": 96
							},
							{ 
								"label": "UVA",
								"value": 116 
							},
							{ 
								"label": "Virginia Tech",
								"value": 117
							},
							{ 
								"label": "Wake",
								"value": 118
							}
						]
					}, 
					{
						"label": "B1G",
						"value": [
							{ 
								"label": "B1G Logo",
								"value": 131 
							},
							{ 
								"label": "Illinois",
								"value": 39 
							},
							{ 
								"label": "Indiana",
								"value": 40 
							},
							{ 
								"label": "Iowa",
								"value": 41 
							},
							{ 
								"label": "Maryland",
								"value": 53 
							},
							{ 
								"label": "Michigan",
								"value": 58 
							},
							{ 
								"label": "Minnesota",
								"value": 61 
							},
							{ 
								"label": "Nebraska",
								"value": 66 
							},
							{ 
								"label": "Northwestern",
								"value": 74 
							},
							{ 
								"label": "Ohio State",
								"value": 76 
							},
							{ 
								"label": "Penn State",
								"value": 83 
							},
							{ 
								"label": "Purdue",
								"value": 85
							},
							{ 
								"label": "Rutgers",
								"value": 87 
							},
							{ 
								"label": "Wisconsin",
								"value": 122
							}
						]
					}, 
					{
						"label": "Big 12",
						"value": [
							{ 
								"label": "Big 12 Logo",
								"value": 132 
							},
							{ 
								"label": "Baylor",
								"value": 10 
							},
							{ 
								"label": "Iowa State",
								"value": 42 
							},
							{ 
								"label": "Kansas",
								"value": 43 
							},
							{ 
								"label": "Kansas State",
								"value": 44 
							},
							{ 
								"label": "Oklahoma",
								"value": 78 
							},
							{ 
								"label": "Oklahoma State",
								"value": 79 
							},
							{ 
								"label": "Texas",
								"value": 100 
							},
							{ 
								"label": "TCU",
								"value": 97 
							},
							{ 
								"label": "Texas Tech",
								"value": 103 
							},
							{ 
								"label": "WVU",
								"value": 124 
							}
						]
					}, 
					{
						"label": "C-USA",
						"value": [
							{ 
								"label": "C-USA Logo",
								"value": 133
							},
							{ 
								"label": "UAB",
								"value": 126 
							},
							{ 
								"label": "FAU",
								"value": 28 
							},
							{ 
								"label": "FIU",
								"value": 29 
							},
							{ 
								"label": "Louisiana Tech",
								"value": 47 
							},
							{ 
								"label": "Marshall",
								"value": 52 
							},
							{ 
								"label": "Middle Tennessee State",
								"value": 60 
							},
							{ 
								"label": "UNC-Charlotte",
								"value": 110 
							},
							{ 
								"label": "North Texas",
								"value": 72 
							},
							{ 
								"label": "ODU",
								"value": 80 
							},
							{ 
								"label": "Rice",
								"value": 86 
							},
							{ 
								"label": "Southern Miss",
								"value": 94 
							},
							{ 
								"label": "UTEP",
								"value": 114 
							},
							{ 
								"label": "UTSA",
								"value": 104 
							},
							{ 
								"label": "WKU",
								"value": 123 
							}
						]
					}, 
					{
						"label": "Independent",
						"value": [
							{ 
								"label": "Army",
								"value": 7
							},
							{ 
								"label": "Navy",
								"value": 65 
							},
							{ 
								"label": "Notre Dame",
								"value": 75 
							},
							{ 
								"label": "BYU",
								"value": 14 
							}
						]
					}, 
					{
						"label": "MAC",
						"value": [
							{ 
								"label": "MAC Logo",
								"value": 134
							},
							{ 
								"label": "Akron",
								"value": 2 
							},
							{ 
								"label": "Ball State",
								"value": 9 
							},
							{ 
								"label": "Bowling Green",
								"value": 13 
							},
							{ 
								"label": "Buffalo",
								"value": 15 
							},
							{ 
								"label": "Central Michigan",
								"value": 18 
							},
							{ 
								"label": "Eastern Michigan",
								"value": 26 
							},
							{ 
								"label": "Kent State",
								"value": 45 
							},
							{ 
								"label": "UMass",
								"value": 54 
							},
							{ 
								"label": "Miami (OH)",
								"value": 57 
							},
							{ 
								"label": "NIU",
								"value": 73 
							},
							{ 
								"label": "Ohio",
								"value": 77 
							},
							{ 
								"label": "Toledo",
								"value": 105 
							},
							{ 
								"label": "Western Michigan",
								"value": 121 
							}
						]
					}, 
					{
						"label": "MWC",
						"value": [
							{ 
								"label": "MWC Logo",
								"value": 135
							},
							{ 
								"label": "Air Force",
								"value": 1 
							},
							{ 
								"label": "Boise State",
								"value": 11 
							},
							{ 
								"label": "Fresno State",
								"value": 31 
							},
							{ 
								"label": "Colorado State",
								"value": 22 
							},
							{ 
								"label": "Hawaii",
								"value": 36 
							},
							{ 
								"label": "Nevada",
								"value": 67 
							},
							{ 
								"label": "UNLV",
								"value": 111 
							},
							{ 
								"label": "New Mexico",
								"value": 68 
							},
							{ 
								"label": "San Diego State",
								"value": 88 
							},
							{ 
								"label": "San Jose State",
								"value": 89 
							},
							{ 
								"label": "Utah State",
								"value": 113 
							},
							{ 
								"label": "Whyoming",
								"value": 125 
							}
						]
					}, 
					{
						"label": "Pac-12",
						"value": [
							{ 
								"label": "Pac-12 Logo",
								"value": 136
							},
							{ 
								"label": "Arizona",
								"value": 5 
							},
							{ 
								"label": "Arizona State",
								"value": 6 
							},
							{ 
								"label": "Cal",
								"value": 16 
							},
							{ 
								"label": "UCLA",
								"value": 109 
							},
							{ 
								"label": "Colorado",
								"value": 21 
							},
							{ 
								"label": "Oregon",
								"value": 81 
							},
							{ 
								"label": "Oregon State",
								"value": 82 
							},
							{ 
								"label": "Southern Cal",
								"value": 93 
							},
							{ 
								"label": "Stanford",
								"value": 95 
							},
							{ 
								"label": "Utah",
								"value": 112 
							},
							{ 
								"label": "Washington",
								"value": 119 
							},
							{ 
								"label": "Washington State",
								"value": 120 
							}
						]
					}, 
					{
						"label": "SEC",
						"value": [
							{ 
								"label": "SEC Logo",
								"value": 137
							},
							{ 
								"label": "Alabama",
								"value": 3 
							},
							{ 
								"label": "Arkansas",
								"value": 140 
							},
							{ 
								"label": "Auburn",
								"value": 8 
							},
							{ 
								"label": "Florida",
								"value": 27 
							},
							{ 
								"label": "Georgia",
								"value": 32 
							},
							{ 
								"label": "Kentucky",
								"value": 46 
							},
							{ 
								"label": "LSU",
								"value": 51 
							},
							{ 
								"label": "Ole Miss",
								"value": 62 
							},
							{ 
								"label": "Mississippi State",
								"value": 63 
							},
							{ 
								"label": "Missouri",
								"value": 64 
							},
							{ 
								"label": "South Carolina",
								"value": 0 
							},
							{ 
								"label": "Tennessee",
								"value": 99 
							},
							{ 
								"label": "Texas A&M",
								"value": 101 
							},
							{ 
								"label": "Vanderbilt",
								"value": 115 
							}
						]
					}, 
					{
						"label": "Sun Belt",
						"value": [
							{ 
								"label": "Sun Belt Logo",
								"value": 138
							},
							{ 
								"label": "App State",
								"value": 4 
							},
							{ 
								"label": "Arkansas State",
								"value": 141 
							},
							{ 
								"label": "Georgia Southern",
								"value": 33 
							},
							{ 
								"label": "Georgia State",
								"value": 34 
							},
							{ 
								"label": "Idaho",
								"value": 38 
							},
							{ 
								"label": "UL-Lafayette",
								"value": 48 
							},
							{ 
								"label": "UL_Monroe",
								"value": 49 
							},
							{ 
								"label": "New Mexico State",
								"value": 69 
							},
							{ 
								"label": "South Alabama",
								"value": 91 
							},
							{ 
								"label": "Texas State",
								"value": 102 
							},
							{ 
								"label": "Troy",
								"value": 106 
							}
						]
					}, 
					{
						"label": "Other",
						"value": [
							{ 
								"label": "NCAA Logo",
								"value": 127
							},
							{ 
								"label": "CFB Playoff Logo",
								"value": 128 
							},
							{ 
								"label": "Team Chaos",
								"value": 139 
							},
							{ 
								"label": "Team Meteor",
								"value": 142 
							}
						]
					}
				]
			},
			{
				"type": "select",
				"capabilities": ["PLATFORM_APLITE"],
				"messageKey": "TEAM",
				"defaultValue": "0",
				"label": "Favorite Team",
				"options": [
					{
						"label": "AAC",
						"value": [
							{ 
								"label": "UCF",
								"value": 17 
							},
							{ 
								"label": "Cincinnati",
								"value": 19 
							},
							{ 
								"label": "UConn",
								"value": 23 
							},
							{ 
								"label": "ECU",
								"value": 25 
							},
							{ 
								"label": "Houston",
								"value": 37 
							},
							{ 
								"label": "Memphis",
								"value": 55 
							},
							{ 
								"label": "USF",
								"value": 92 
							},
							{ 
								"label": "SMU",
								"value": 90 
							},
							{ 
								"label": "Temple",
								"value": 98 
							},
							{ 
								"label": "Tulane",
								"value": 107
							},
							{ 
								"label": "Tulsa",
								"value": 108 
							}
						]
					}, 
					{
						"label": "ACC",
						"value": [
							{ 
								"label": "Boston College",
								"value": 12 
							},
							{ 
								"label": "Clemson",
								"value": 20 
							},
							{ 
								"label": "Duke",
								"value": 24 
							},
							{ 
								"label": "FSU",
								"value": 30 
							},
							{ 
								"label": "Georgia Tech",
								"value": 35 
							},
							{ 
								"label": "Louisville",
								"value": 50 
							},
							{ 
								"label": "Miami",
								"value": 56 
							},
							{ 
								"label": "UNC",
								"value": 70 
							},
							{ 
								"label": "NC State",
								"value": 71 
							},
							{ 
								"label": "Pitt",
								"value": 84 
							},
							{ 
								"label": "Syracuse",
								"value": 96
							},
							{ 
								"label": "UVA",
								"value": 116 
							},
							{ 
								"label": "Virginia Tech",
								"value": 117
							},
							{ 
								"label": "Wake",
								"value": 118
							}
						]
					}, 
					{
						"label": "B1G",
						"value": [
							{ 
								"label": "Illinois",
								"value": 39 
							},
							{ 
								"label": "Indiana",
								"value": 40 
							},
							{ 
								"label": "Iowa",
								"value": 41 
							},
							{ 
								"label": "Maryland",
								"value": 53 
							},
							{ 
								"label": "Michigan",
								"value": 58 
							},
							{ 
								"label": "Minnesota",
								"value": 61 
							},
							{ 
								"label": "Nebraska",
								"value": 66 
							},
							{ 
								"label": "Northwestern",
								"value": 74 
							},
							{ 
								"label": "Ohio State",
								"value": 76 
							},
							{ 
								"label": "Penn State",
								"value": 83 
							},
							{ 
								"label": "Purdue",
								"value": 85
							},
							{ 
								"label": "Rutgers",
								"value": 87 
							},
							{ 
								"label": "Wisconsin",
								"value": 122
							}
						]
					}, 
					{
						"label": "Big 12",
						"value": [
							{ 
								"label": "Baylor",
								"value": 10 
							},
							{ 
								"label": "Iowa State",
								"value": 42 
							},
							{ 
								"label": "Kansas",
								"value": 43 
							},
							{ 
								"label": "Kansas State",
								"value": 44 
							},
							{ 
								"label": "Oklahoma",
								"value": 78 
							},
							{ 
								"label": "Oklahoma State",
								"value": 79 
							},
							{ 
								"label": "Texas",
								"value": 100 
							},
							{ 
								"label": "TCU",
								"value": 97 
							},
							{ 
								"label": "Texas Tech",
								"value": 103 
							},
							{ 
								"label": "WVU",
								"value": 124 
							}
						]
					}, 
					{
						"label": "Independent",
						"value": [
							{ 
								"label": "Army",
								"value": 7
							},
							{ 
								"label": "Navy",
								"value": 65 
							},
							{ 
								"label": "Notre Dame",
								"value": 75 
							},
							{ 
								"label": "BYU",
								"value": 14 
							}
						]
					}, 
					{
						"label": "MAC",
						"value": [
							{ 
								"label": "Akron",
								"value": 2 
							},
							{ 
								"label": "Ball State",
								"value": 9 
							},
							{ 
								"label": "Bowling Green",
								"value": 13 
							},
							{ 
								"label": "Buffalo",
								"value": 15 
							},
							{ 
								"label": "Central Michigan",
								"value": 18 
							},
							{ 
								"label": "Eastern Michigan",
								"value": 26 
							},
							{ 
								"label": "Kent State",
								"value": 45 
							},
							{ 
								"label": "UMass",
								"value": 54 
							},
							{ 
								"label": "Miami (OH)",
								"value": 57 
							},
							{ 
								"label": "NIU",
								"value": 73 
							},
							{ 
								"label": "Ohio",
								"value": 77 
							},
							{ 
								"label": "Toledo",
								"value": 105 
							},
							{ 
								"label": "Western Michigan",
								"value": 121 
							}
						]
					}, 
					{
						"label": "MWC",
						"value": [
							{ 
								"label": "Air Force",
								"value": 1 
							},
							{ 
								"label": "Boise State",
								"value": 11 
							},
							{ 
								"label": "Fresno State",
								"value": 31 
							},
							{ 
								"label": "Colorado State",
								"value": 22 
							},
							{ 
								"label": "Hawaii",
								"value": 36 
							},
							{ 
								"label": "Nevada",
								"value": 67 
							},
							{ 
								"label": "UNLV",
								"value": 111 
							},
							{ 
								"label": "New Mexico",
								"value": 68 
							},
							{ 
								"label": "San Diego State",
								"value": 88 
							},
							{ 
								"label": "San Jose State",
								"value": 89 
							},
							{ 
								"label": "Utah State",
								"value": 113 
							},
							{ 
								"label": "Whyoming",
								"value": 125 
							}
						]
					}, 
					{
						"label": "Pac-12",
						"value": [
							{ 
								"label": "Arizona",
								"value": 5 
							},
							{ 
								"label": "Arizona State",
								"value": 6 
							},
							{ 
								"label": "Cal",
								"value": 16 
							},
							{ 
								"label": "UCLA",
								"value": 109 
							},
							{ 
								"label": "Colorado",
								"value": 21 
							},
							{ 
								"label": "Oregon",
								"value": 81 
							},
							{ 
								"label": "Oregon State",
								"value": 82 
							},
							{ 
								"label": "Southern Cal",
								"value": 93 
							},
							{ 
								"label": "Stanford",
								"value": 95 
							},
							{ 
								"label": "Utah",
								"value": 112 
							},
							{ 
								"label": "Washington",
								"value": 119 
							},
							{ 
								"label": "Washington State",
								"value": 120 
							}
						]
					}, 
					{
						"label": "SEC",
						"value": [
							{ 
								"label": "Alabama",
								"value": 3 
							},
							{ 
								"label": "Arkansas",
								"value": 140 
							},
							{ 
								"label": "Auburn",
								"value": 8 
							},
							{ 
								"label": "Florida",
								"value": 27 
							},
							{ 
								"label": "Georgia",
								"value": 32 
							},
							{ 
								"label": "Kentucky",
								"value": 46 
							},
							{ 
								"label": "LSU",
								"value": 51 
							},
							{ 
								"label": "Ole Miss",
								"value": 62 
							},
							{ 
								"label": "Mississippi State",
								"value": 63 
							},
							{ 
								"label": "Missouri",
								"value": 64 
							},
							{ 
								"label": "South Carolina",
								"value": 0 
							},
							{ 
								"label": "Tennessee",
								"value": 99 
							},
							{ 
								"label": "Texas A&M",
								"value": 101 
							},
							{ 
								"label": "Vanderbilt",
								"value": 115 
							}
						]
					}, 
					{
						"label": "Sun Belt",
						"value": [
							{ 
								"label": "App State",
								"value": 4 
							},
							{ 
								"label": "Arkansas State",
								"value": 141 
							},
							{ 
								"label": "Georgia Southern",
								"value": 33 
							},
							{ 
								"label": "Georgia State",
								"value": 34 
							},
							{ 
								"label": "Idaho",
								"value": 38 
							},
							{ 
								"label": "UL-Lafayette",
								"value": 48 
							},
							{ 
								"label": "UL_Monroe",
								"value": 49 
							},
							{ 
								"label": "New Mexico State",
								"value": 69 
							},
							{ 
								"label": "South Alabama",
								"value": 91 
							},
							{ 
								"label": "Texas State",
								"value": 102 
							},
							{ 
								"label": "Troy",
								"value": 106 
							}
						]
					}, 
					{
						"label": "Other",
						"value": [
							{ 
								"label": "NCAA Logo",
								"value": 127
							},
							{ 
								"label": "CFB Playoff Logo",
								"value": 128 
							}
						]
					}
				]
			},
			{
				"type": "select",
				"capabilities": ["PLATFORM_APLITE"],
				"messageKey": "BADTEAM",
				"defaultValue": "20",
				"label": "Team You Want to Beat",
				"options": [
					{
						"label": "AAC",
						"value": [
							{ 
								"label": "UCF",
								"value": 17 
							},
							{ 
								"label": "Cincinnati",
								"value": 19 
							},
							{ 
								"label": "UConn",
								"value": 23 
							},
							{ 
								"label": "ECU",
								"value": 25 
							},
							{ 
								"label": "Houston",
								"value": 37 
							},
							{ 
								"label": "Memphis",
								"value": 55 
							},
							{ 
								"label": "USF",
								"value": 92 
							},
							{ 
								"label": "SMU",
								"value": 90 
							},
							{ 
								"label": "Temple",
								"value": 98 
							},
							{ 
								"label": "Tulane",
								"value": 107
							},
							{ 
								"label": "Tulsa",
								"value": 108 
							}
						]
					}, 
					{
						"label": "ACC",
						"value": [
							{ 
								"label": "Boston College",
								"value": 12 
							},
							{ 
								"label": "Clemson",
								"value": 20 
							},
							{ 
								"label": "Duke",
								"value": 24 
							},
							{ 
								"label": "FSU",
								"value": 30 
							},
							{ 
								"label": "Georgia Tech",
								"value": 35 
							},
							{ 
								"label": "Louisville",
								"value": 50 
							},
							{ 
								"label": "Miami",
								"value": 56 
							},
							{ 
								"label": "UNC",
								"value": 70 
							},
							{ 
								"label": "NC State",
								"value": 71 
							},
							{ 
								"label": "Pitt",
								"value": 84 
							},
							{ 
								"label": "Syracuse",
								"value": 96
							},
							{ 
								"label": "UVA",
								"value": 116 
							},
							{ 
								"label": "Virginia Tech",
								"value": 117
							},
							{ 
								"label": "Wake",
								"value": 118
							}
						]
					}, 
					{
						"label": "B1G",
						"value": [
							{ 
								"label": "Illinois",
								"value": 39 
							},
							{ 
								"label": "Indiana",
								"value": 40 
							},
							{ 
								"label": "Iowa",
								"value": 41 
							},
							{ 
								"label": "Maryland",
								"value": 53 
							},
							{ 
								"label": "Michigan",
								"value": 58 
							},
							{ 
								"label": "Minnesota",
								"value": 61 
							},
							{ 
								"label": "Nebraska",
								"value": 66 
							},
							{ 
								"label": "Northwestern",
								"value": 74 
							},
							{ 
								"label": "Ohio State",
								"value": 76 
							},
							{ 
								"label": "Penn State",
								"value": 83 
							},
							{ 
								"label": "Purdue",
								"value": 85
							},
							{ 
								"label": "Rutgers",
								"value": 87 
							},
							{ 
								"label": "Wisconsin",
								"value": 122
							}
						]
					}, 
					{
						"label": "Big 12",
						"value": [
							{ 
								"label": "Baylor",
								"value": 10 
							},
							{ 
								"label": "Iowa State",
								"value": 42 
							},
							{ 
								"label": "Kansas",
								"value": 43 
							},
							{ 
								"label": "Kansas State",
								"value": 44 
							},
							{ 
								"label": "Oklahoma",
								"value": 78 
							},
							{ 
								"label": "Oklahoma State",
								"value": 79 
							},
							{ 
								"label": "Texas",
								"value": 100 
							},
							{ 
								"label": "TCU",
								"value": 97 
							},
							{ 
								"label": "Texas Tech",
								"value": 103 
							},
							{ 
								"label": "WVU",
								"value": 124 
							}
						]
					}, 
					{
						"label": "Independent",
						"value": [
							{ 
								"label": "Army",
								"value": 7
							},
							{ 
								"label": "Navy",
								"value": 65 
							},
							{ 
								"label": "Notre Dame",
								"value": 75 
							},
							{ 
								"label": "BYU",
								"value": 14 
							}
						]
					}, 
					{
						"label": "MAC",
						"value": [
							{ 
								"label": "Akron",
								"value": 2 
							},
							{ 
								"label": "Ball State",
								"value": 9 
							},
							{ 
								"label": "Bowling Green",
								"value": 13 
							},
							{ 
								"label": "Buffalo",
								"value": 15 
							},
							{ 
								"label": "Central Michigan",
								"value": 18 
							},
							{ 
								"label": "Eastern Michigan",
								"value": 26 
							},
							{ 
								"label": "Kent State",
								"value": 45 
							},
							{ 
								"label": "UMass",
								"value": 54 
							},
							{ 
								"label": "Miami (OH)",
								"value": 57 
							},
							{ 
								"label": "NIU",
								"value": 73 
							},
							{ 
								"label": "Ohio",
								"value": 77 
							},
							{ 
								"label": "Toledo",
								"value": 105 
							},
							{ 
								"label": "Western Michigan",
								"value": 121 
							}
						]
					}, 
					{
						"label": "MWC",
						"value": [
							{ 
								"label": "Air Force",
								"value": 1 
							},
							{ 
								"label": "Boise State",
								"value": 11 
							},
							{ 
								"label": "Fresno State",
								"value": 31 
							},
							{ 
								"label": "Colorado State",
								"value": 22 
							},
							{ 
								"label": "Hawaii",
								"value": 36 
							},
							{ 
								"label": "Nevada",
								"value": 67 
							},
							{ 
								"label": "UNLV",
								"value": 111 
							},
							{ 
								"label": "New Mexico",
								"value": 68 
							},
							{ 
								"label": "San Diego State",
								"value": 88 
							},
							{ 
								"label": "San Jose State",
								"value": 89 
							},
							{ 
								"label": "Utah State",
								"value": 113 
							},
							{ 
								"label": "Whyoming",
								"value": 125 
							}
						]
					}, 
					{
						"label": "Pac-12",
						"value": [
							{ 
								"label": "Arizona",
								"value": 5 
							},
							{ 
								"label": "Arizona State",
								"value": 6 
							},
							{ 
								"label": "Cal",
								"value": 16 
							},
							{ 
								"label": "UCLA",
								"value": 109 
							},
							{ 
								"label": "Colorado",
								"value": 21 
							},
							{ 
								"label": "Oregon",
								"value": 81 
							},
							{ 
								"label": "Oregon State",
								"value": 82 
							},
							{ 
								"label": "Southern Cal",
								"value": 93 
							},
							{ 
								"label": "Stanford",
								"value": 95 
							},
							{ 
								"label": "Utah",
								"value": 112 
							},
							{ 
								"label": "Washington",
								"value": 119 
							},
							{ 
								"label": "Washington State",
								"value": 120 
							}
						]
					}, 
					{
						"label": "SEC",
						"value": [
							{ 
								"label": "Alabama",
								"value": 3 
							},
							{ 
								"label": "Arkansas",
								"value": 140 
							},
							{ 
								"label": "Auburn",
								"value": 8 
							},
							{ 
								"label": "Florida",
								"value": 27 
							},
							{ 
								"label": "Georgia",
								"value": 32 
							},
							{ 
								"label": "Kentucky",
								"value": 46 
							},
							{ 
								"label": "LSU",
								"value": 51 
							},
							{ 
								"label": "Ole Miss",
								"value": 62 
							},
							{ 
								"label": "Mississippi State",
								"value": 63 
							},
							{ 
								"label": "Missouri",
								"value": 64 
							},
							{ 
								"label": "South Carolina",
								"value": 0 
							},
							{ 
								"label": "Tennessee",
								"value": 99 
							},
							{ 
								"label": "Texas A&M",
								"value": 101 
							},
							{ 
								"label": "Vanderbilt",
								"value": 115 
							}
						]
					}, 
					{
						"label": "Sun Belt",
						"value": [
							{ 
								"label": "App State",
								"value": 4 
							},
							{ 
								"label": "Arkansas State",
								"value": 141 
							},
							{ 
								"label": "Georgia Southern",
								"value": 33 
							},
							{ 
								"label": "Georgia State",
								"value": 34 
							},
							{ 
								"label": "Idaho",
								"value": 38 
							},
							{ 
								"label": "UL-Lafayette",
								"value": 48 
							},
							{ 
								"label": "UL_Monroe",
								"value": 49 
							},
							{ 
								"label": "New Mexico State",
								"value": 69 
							},
							{ 
								"label": "South Alabama",
								"value": 91 
							},
							{ 
								"label": "Texas State",
								"value": 102 
							},
							{ 
								"label": "Troy",
								"value": 106 
							}
						]
					}, 
					{
						"label": "Other",
						"value": [
							{ 
								"label": "NCAA Logo",
								"value": 127
							},
							{ 
								"label": "CFB Playoff Logo",
								"value": 128 
							}
						]
					}
				]
			}
		]
	},
	{
		"type": "section",
		"capabilities": ["NOT_PLATFORM_APLITE"],
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
  "capabilities": ["HEALTH", "NOT_PLATFORM_APLITE"],
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