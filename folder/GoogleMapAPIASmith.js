/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
var map;
var mark; 
//'{ "Marker" : [ {"position": {"lat":-34.397 , "lng":150.644}}]}';
var datain;
var markerArr;
var curPos;
var timer;
  
  function clearMap(){
       for (let i = 0; i < markerArr.length; i++)
      { markerArr[i].setMap(null); }
      markerArr.length = 0;   
  }
  
  function markMap(){
     
     // var t = setTimeout(console.log(datain), 1000);
      let obj = JSON.parse(datain);
      //markerArr[0] = new google.maps.Marker({position: obj[0].position, map:map, label: obj[0].label});
      //mark.setMap(null);
      for (let j = 0; j<2; j++){
      for (let i = 0; i <obj.length; i++)
      { markerArr[i] = new google.maps.Marker({position: obj[i].position, map:map, label: obj[i].label});}
      }
      //mark.setMap(map);
      
      
  };

      


  function initMap() {
      

      
    map = new google.maps.Map(document.getElementById('map'), {
      center: {lat: 32.231884, lng: -110.950111},
      zoom: 20,
      mapTypeId:'hybrid'

    });
    

    mark = new google.maps.Marker({
          position: {lat: 32.231904, lng: -110.950111},
          map: null,
          label: "Debug"
          });
    
    markerArr = [new google.maps.Marker({position: {lat: 32.231884, lng: -110.950111}, map:map, label: "one"}),
                new google.maps.Marker({position: {lat: 32.231984, lng: -110.950011}, map:map, label: "two"}),
                new google.maps.Marker({position: {lat: 32.231784, lng: -110.950211}, map:null, label:"three"})];
    
    let fun = [];
            fun[0] = MarkerToCoordinates(markerArr[0]);
    for (let i = 1; i<markerArr.length; i++){
        fun[i] = MarkerToCoordinates(markerArr[i]);
        
    }
    
    datain = JSON.stringify(fun);
    markerArr[1].setMap(null);
    
    //var dev = setTimeout(function(){alert("hello");},15000);
    //mark.setMap(map);
    
    timer = [setInterval(markMap, 15), setInterval(clearMap, 500)];
    
}

function MarkerToCoordinates(marker){
    let pos = marker.position;
//    let lati = pos.lat;
//    let long = pos.lng;
    let labely = marker.label;
    let coordinates = {position: pos, label:labely};
    return coordinates;
}

