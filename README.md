MIPSR10K
========

MIPS R10000 architecture simulator with C++ 

**Table of Contents**

- [Software architecture](#software-architecture)
	- [Document history with TimelineJS](#document-history-with-timelinejs)
	- [Add it to your site](#add-it-to-your-site)
		- [Using Inline (easiest)](#using-inline-easiest)
			- [Using Inline (easiest)]
		- [Using a method (advanced)](#using-a-method-advanced)
		- [Loading the files](#loading-the-files)
	- [Config Options](#config-options)
		- [Language](#language)
		- [Start at End](#start-at-end)
		- [Start at Slide](#start-at-slide)
		- [Start Zoom Adjust](#start-zoom-adjust)
		- [Hash Bookmark](#hash-bookmark)
		- [Debug](#debug)
		- [Map Style Types](#map-style-types)
		- [Font Options](#font-options)
			- [Font Combination Preview:](#font-combination-preview)
	- [File Formats](#file-formats)
		- [JSON:](#json)
		- [JSONP :](#jsonp-)
		- [Google Docs:](#google-docs)
		- [Storify:](#storify)
	- [Media](#media)
	- [Best practices](#best-practices)
	- [License](#license)
	
## Software architecture 
## Document history with TimelineJS
## Add it to your site
### Using Inline (*easiest*)
Place the embed code where you want the timeline to show in the `<body>` of your site. See [Config Options](#config-options) for a full list of what you can set in the config.

```html
	<div id="timeline-embed"></div>
	<script type="text/javascript">
	    var timeline_config = {
			width:				'100%',
			height:				'600',
			source:				'path_to_json/or_link_to_googlespreadsheet',
			embed_id:			'timeline-embed',				//OPTIONAL USE A DIFFERENT DIV ID FOR EMBED
			start_at_end: 		false,							//OPTIONAL START AT LATEST DATE
			start_at_slide:		'4',							//OPTIONAL START AT SPECIFIC SLIDE
			start_zoom_adjust:	'3',							//OPTIONAL TWEAK THE DEFAULT ZOOM LEVEL
			hash_bookmark:		true,							//OPTIONAL LOCATION BAR HASHES
			font:				'Bevan-PotanoSans',				//OPTIONAL FONT
			debug:				true,							//OPTIONAL DEBUG TO CONSOLE
			lang:				'fr',							//OPTIONAL LANGUAGE
			maptype:			'watercolor',					//OPTIONAL MAP STYLE
			css:				'path_to_css/timeline.css',		//OPTIONAL PATH TO CSS
			js:					'path_to_js/timeline-min.js'	//OPTIONAL PATH TO JS
		}
	</script>
	<script type="text/javascript" src="http://cdn.knightlab.com/libs/timeline/latest/js/storyjs-embed.js"></script>
```
	
## Config Options
Here are some of the options you can set in the config.

### Source
`source` Should be either the path to the JSON resource to load, or a JavaScript
object corresponding to the Timeline model.

###Font Options 
`font:`
* `AbrilFatface-Average` *Abril Fatface & Average*
* `Arvo-PTSans` *Arvo & PT Sans*
* `Bevan-PotanoSans` *Bevan & Potano Sans*
* `BreeSerif-OpenSans` *Bree Serif & Open Sans*
* `DroidSerif-DroidSans` *Droid Serif & Droid Sans*
* `Georgia-Helvetica` *Georgia & Helvetica Neue*
* `Lekton-Molengo` *Lekton & Molengo*
* `Merriweather-NewsCycle` *Merriweather & News Cycle*
* `NewsCycle-Merriweather` *News Cycle & Merriweather*
* `NixieOne-Ledger` *Nixie One & Ledger*
* `Pacifico-Arimo` *Pacifico & Arimo*
* `PlayfairDisplay-Muli` *Playfair Display & Muli*
* `PoiretOne-Molengo` *Poiret One & Molengo*
* `PTSerif-PTSans` *PT Serif & PT Sans*
* `PT` *PT Sans & PT Narrow & PT Serif*
* `Rancho-Gudea` *Rancho & Gudea*
* `SansitaOne-Kameron` *Sansita One & Kameron*
* Or make your own

####Font Combination Preview:
![Font Combination Preview](http://timeline.knightlab.com/static/img/make/font-options.png)
  
## License
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.


