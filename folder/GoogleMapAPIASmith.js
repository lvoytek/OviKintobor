/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/* global google */

var map;
var mark; 
//'{ "Marker" : [ {"position": {"lat":-34.397 , "lng":150.644}}]}';
var datain;
var markerArr = [];
var index = 0;
var nextIndex = 0;
var timer;
var timer2;
var timer3;
var droneData;
var canvasContext;
var canvasHeight;
var canvasWidth;
var dev = '{"type":"gps", "datetime":"1/19/2020, 05:35:30", "lat":32.231457, "lng":-110.959012, "altitude":260.700000, "fix":1, "satellites":4, "hdop":3.130000}';
var dev2 = '{"type":"ifr", "data":[[-20,-0.25,-0.25,-0.25,-0.25,-0.25,-0.25,15], [-0.25,-0.25,45,-0.25,-0.25,-0.25,16,0.31], [-0.25,44,22,-0.25,-0.25,-0.25,-0.25,0.31], [-0.25,-0.25,-0.25,55,-0.25,-0.25,-19,0.31], [-0.25,11,11,11,-0.25,11,-0.25,0.31], [35,-0.25,-0.25,-0.25,25,-0.25,-0.25,45], [-0.25,10,20,30,40,50,60,-10], [60,50,40,30,20,30,40,50]]}';
    function readData(){
        //nextIndex = Data.indexOf('\r'); 
        //let string = Data.slice(index,nextIndex);
        //let string = JSON.parse(dev);
        
        markerArr[0].setMap(null);
        let obj;
                try{obj = dev.type;}
                catch(err){ document.getElementById("map").innerHTML = err.message;};
        markerArr[1].setMap(null);
        mark.setLabel(obj);
        
        //index = nextIndex;
        return obj;
    }
  
  function clearMap(){
       for (let i = 0; i < markerArr.length; i++)
      { markerArr[i].setMap(null); }
      markerArr.length = 0;
  }
  
  function markMap(){
     
     // var t = setTimeout(console.log(datain), 1000);
      
      //markerArr[0] = new google.maps.Marker({position: obj[0].position, map:map, label: obj[0].label});
      //mark.setMap(null);
     // for (let j = 0; j<2; j++){
//     if(markerArr.length == 0){
      markerArr[0] = new google.maps.Marker({position: {lat: droneData.lat, lng: droneData.lng}, map:map, label: droneData.altitude + ""});
//      else
//      {markerArr[markerArr.length] = new google.maps.Marker({position: {lat: datain.lat, lng: datain.lng}, map:map, label: datain.altitude});}
      //}
      //mark.setMap(map);
      
      
  };

    function updateCam()
    {
        for(i = 0; i < 8; i++){
            for(j = 0; j<8; j++)
            {
                let color = hexString = parseInt(droneData.data[i][j]*255/40 + 255/20).toString(16);
                canvasContext.fillStyle = "#" + color + "0000";
//                canvasContext.fillRect(i*50,j*50,25,25);
                canvasContext.fillRect(i*canvasWidth/8,j*canvasHeight/8,canvasWidth/8,canvasHeight/8);
            }
            
        }
    };


  function initMapAndCam() {
    
    
    
//    let lat = droneData[0].lat;
//    let lng = droneData[0].lng;
//    let alt = droneData[0].altitude;
      
    map = new google.maps.Map(document.getElementById('map'), {
      center: {lat: 32.229715, lng: -110.9553111},
      zoom: 16,
      mapTypeId:'hybrid'

    });
    
    cam = document.getElementById('cam');
    canvasContext = cam.getContext("2d");
    canvasWidth = cam.width;
    canvasHeight = cam.height;
//    canvasContext.fillRect(50,50,50,50);
//    canvasContext.fillStyle = "#FF0000";
//    canvasContext.fillRect(100,100,25,25);
    
    
    
    mark = new google.maps.Marker({
          position: {lat: 32.229715, lng: -110.9553111},
          map: map,
          label: "Data"
          });
          
          
//    markMap();
        parseData(dev2);
        parseData(dev);
        



        
////    
//    markerArr = [new google.maps.Marker({position: {lat: 32.228215, lng: -110.9549211}, map:map, label: "one"}),
//                new google.maps.Marker({position: {lat: 32.229615, lng: -110.9551111}, map:map, label: "two"}),
//                new google.maps.Marker({position: {lat: 32.230815, lng: -110.9553011}, map:null, label:"three"})];
//    readData();
//    let fun = [];
//            fun[0] = MarkerToCoordinates(markerArr[0]);
//    for (let i = 1; i<markerArr.length; i++){
//        fun[i] = MarkerToCoordinates(markerArr[i]);
//        
//    }
//    
//    datain = JSON.stringify(fun);
//    markerArr[1].setMap(null);
    
    //var dev = setTimeout(function(){alert("hello");},15000);
    //mark.setMap(map);
   //timer = setInterval(parseData, 100);
   //timer2 = setInterval(clearMap, 1000); 
    timer = [setInterval(clearMap, 50), setInterval(markMap, 15)];
    
}

function MarkerToCoordinates(marker){
    let pos = marker.position;
//    let lati = pos.lat;
//    let long = pos.lng;
    let labely = marker.label;
    let coordinates = {position: pos, label:labely};
    return coordinates;
}

function parseData(d){
    let string = d;
    
    droneData = JSON.parse(string);

    if (droneData.type == "gps"){
        markMap();
    }
    else if (droneData.type == "ifr"){
//        updateCam(droneData.data);
          updateCam();
    }
}
