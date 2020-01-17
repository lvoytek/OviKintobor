/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
var map;
var mark; 
//'{ "Marker" : [ {"position": {"lat":-34.397 , "lng":150.644}}]}';
var datain;
var markerArr = [];
var curPos;


  function markMap(map, datain){
      for (var i = 0; i < markerArr.length; i++)
      { markerArr[i].setMap(null); }
      markerArr.length = 0;
      
      markerArr = JSON.parse(datain);
      for (var i = 0; i < markerArr.length; i++)
      { markerArr[i].setMap(map); }
      //marker.setMap(map);
      
  };

      


  function initMap() {
      

      
    map = new google.maps.Map(document.getElementById('map'), {
      center: {lat: 32.231884, lng: -110.950111},
      zoom: 10
      //mapTypeId:'satellite',
    });
    

    let mark = new google.maps.Marker({
          position: {lat: 32.231884, lng: -110.950111},
          map: map
          });
    
          
    datain = JSON.stringify(mark);
    var timer = setInterval(markMap(map, datain), 100);
}



