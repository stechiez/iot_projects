const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>STechiezDIY</title>
    <style>
        body {
            display: flex;
            justify-content: center;
            align-items: flex-start;
            height: 100vh;
            margin: 0;
            background-color: #282c34;
            color: white;
            font-family: Arial, sans-serif;
        }
        .center-content {
            text-align: center;
            margin-top: 50px;
        }
        h1 {
            font-size: 4em;
            margin-bottom: 20px;
        }
        .adc-value {
            margin: 20px 0;
            font-size: 3em;
            font-weight: bold;
            color: #61dafb;
        }
        .button {
            margin: 10px;
            padding: 20px 40px;
            font-size: 2em;
            cursor: pointer;
            border: none;
            border-radius: 5px;
            background-color: #61dafb;
            color: #282c34;
            transition: background-color 0.3s, color 0.3s;
        }
        .button:hover {
            background-color: #21a1f1;
            color: white;
        }
    </style>
</head>
<body>
    <div class="center-content">
        <h1>STechiezDIY</h1>
        <div class="adc-value">ADC Value: <span id="adcValue">0</span></div>
        <button class="button" onclick="openYouTube()">Open YouTube</button>
        <button class="button" onclick="toggleLED()">LED Switch</button>
    </div>

    <script>
        function openYouTube() {
            window.open('https://www.youtube.com/@StechiezDIY?sub_confirmation=1', '_blank');
        }

        function toggleLED() {
            var xhttp = new XMLHttpRequest();
            // Here you can add the code to toggle the LED.
            // For demonstration, we just log to the console.
            
            alert('LED toggled');  // Showing an alert for visual feedback
            xhttp.open("GET", "led_toggle", true);
            xhttp.send();
        }
        
        function getADCValue() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("adcValue").innerHTML =
            this.responseText;
          }
        };
        xhttp.open("GET", "adc_value", true);
        xhttp.send();
      }
        
        // Simulate ADC value update
        setInterval(() => {
            // Generate a random ADC value for demonstration
            //const adcValue = Math.floor(Math.random() * 1024);
            //document.getElementById('adcValue').innerText = adcValue;
            getADCValue();
        }, 1000);  // Update every second
    </script>
</body>
</html>

)rawliteral";
