PGM_P(ajaxscript) =
  "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script>"
  "<script>"
  "function gt(n){$.ajax({url:'tt',success:function(result){{$('#tt').html(result);}}});}"              // reloj
  "function gf(n){$.ajax({url:'f'+n,success:function(result){{$('#f'+n).html(result);}}});}"            // data
  "function gl(n){$.ajax({url:'l'+n,success:function(result){{$('#l'+n).html(result);}}});}"            // data
  "function chf(){for(i=7;i<8;i++){gf(i);}setTimeout(function(){chf();},100);}"                  // cada 0.1 seg.
  "function ch(){gt(0);for(i=0;i<7;i++){gl(i);}setTimeout(function(){ch();},1000);}" // cada 1 seg.
  "chf();ch();"
  "</script>";

