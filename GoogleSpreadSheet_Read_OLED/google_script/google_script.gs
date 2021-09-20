//https://script.google.com/macros/s/AKfycbzdaV09fHKI9EXjSGqsvhULyvYjJPMojpT9nuZ_rPohTW9qkC3sdaBKCO7EEyIpOlHW/exec
var ss = SpreadsheetApp.openById('1WTxdn11J9ATKfBsf8W8xO2NrV_USE4V3TO62bwsRID8');
var sheet = ss.getSheetByName('Sheet1');

function doPost(e) {
  var val = e.parameter.value;
  
  if (e.parameter.value !== undefined){
    var range = sheet.getRange('A2');
    range.setValue(val);
  }
}

function doGet(e){
  var read = e.parameter.read;

  if (read !== undefined){
    return ContentService.createTextOutput(sheet.getRange('C2').getValue());
  }
}

