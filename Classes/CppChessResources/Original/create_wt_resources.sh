convert wood_l.xpm ../ls.png
convert wood_d.xpm ../ds.png
convert question_mark.xpm ../question_mark.png

convert -colorize 0,80,80 ../ls.png ../lsr.png
convert -colorize 0,80,80 ../ds.png ../dsr.png
convert -colorize 80,0,80 ../ls.png ../lsg.png
convert -colorize 80,0,80 ../ds.png ../dsg.png
convert -colorize 80,80,0 ../ls.png ../lsb.png
convert -colorize 80,80,0 ../ds.png ../dsb.png

#Put pieces on ls and ds

#Bishop
convert -transparent green -composite ../ls.png bld129.xpm ../wbls.png
convert -transparent green -composite ../ds.png bld129.xpm ../wbds.png
convert -transparent green -composite ../ls.png bdd129.xpm ../bbls.png
convert -transparent green -composite ../ds.png bdd129.xpm ../bbds.png
#King
convert -transparent green -composite ../ls.png kld129.xpm ../wkls.png
convert -transparent green -composite ../ds.png kld129.xpm ../wkds.png
convert -transparent green -composite ../ls.png kdd129.xpm ../bkls.png
convert -transparent green -composite ../ds.png kdd129.xpm ../bkds.png
#Knight
convert -transparent green -composite ../ls.png nld129.xpm ../wnls.png
convert -transparent green -composite ../ds.png nld129.xpm ../wnds.png
convert -transparent green -composite ../ls.png ndd129.xpm ../bnls.png
convert -transparent green -composite ../ds.png ndd129.xpm ../bnds.png
#Pawn
convert -transparent green -composite ../ls.png pld129.xpm ../wpls.png
convert -transparent green -composite ../ds.png pld129.xpm ../wpds.png
convert -transparent green -composite ../ls.png pdd129.xpm ../bpls.png
convert -transparent green -composite ../ds.png pdd129.xpm ../bpds.png
#Queen
convert -transparent green -composite ../ls.png qld129.xpm ../wqls.png
convert -transparent green -composite ../ds.png qld129.xpm ../wqds.png
convert -transparent green -composite ../ls.png qdd129.xpm ../bqls.png
convert -transparent green -composite ../ds.png qdd129.xpm ../bqds.png
#Rook
convert -transparent green -composite ../ls.png rld129.xpm ../wrls.png
convert -transparent green -composite ../ds.png rld129.xpm ../wrds.png
convert -transparent green -composite ../ls.png rdd129.xpm ../brls.png
convert -transparent green -composite ../ds.png rdd129.xpm ../brds.png

#Put pieces on lsr and dsr

#Bishop
convert -transparent green -composite ../lsr.png bld129.xpm ../wblsr.png
convert -transparent green -composite ../dsr.png bld129.xpm ../wbdsr.png
convert -transparent green -composite ../lsr.png bdd129.xpm ../bblsr.png
convert -transparent green -composite ../dsr.png bdd129.xpm ../bbdsr.png
#King
convert -transparent green -composite ../lsr.png kld129.xpm ../wklsr.png
convert -transparent green -composite ../dsr.png kld129.xpm ../wkdsr.png
convert -transparent green -composite ../lsr.png kdd129.xpm ../bklsr.png
convert -transparent green -composite ../dsr.png kdd129.xpm ../bkdsr.png
#Knight
convert -transparent green -composite ../lsr.png nld129.xpm ../wnlsr.png
convert -transparent green -composite ../dsr.png nld129.xpm ../wndsr.png
convert -transparent green -composite ../lsr.png ndd129.xpm ../bnlsr.png
convert -transparent green -composite ../dsr.png ndd129.xpm ../bndsr.png
#Pawn
convert -transparent green -composite ../lsr.png pld129.xpm ../wplsr.png
convert -transparent green -composite ../dsr.png pld129.xpm ../wpdsr.png
convert -transparent green -composite ../lsr.png pdd129.xpm ../bplsr.png
convert -transparent green -composite ../dsr.png pdd129.xpm ../bpdsr.png
#Queen
convert -transparent green -composite ../lsr.png qld129.xpm ../wqlsr.png
convert -transparent green -composite ../dsr.png qld129.xpm ../wqdsr.png
convert -transparent green -composite ../lsr.png qdd129.xpm ../bqlsr.png
convert -transparent green -composite ../dsr.png qdd129.xpm ../bqdsr.png
#Rook
convert -transparent green -composite ../lsr.png rld129.xpm ../wrlsr.png
convert -transparent green -composite ../dsr.png rld129.xpm ../wrdsr.png
convert -transparent green -composite ../lsr.png rdd129.xpm ../brlsr.png
convert -transparent green -composite ../dsr.png rdd129.xpm ../brdsr.png

#Put pieces on lsg and dsg

#Bishop
convert -transparent green -composite ../lsg.png bld129.xpm ../wblsg.png
convert -transparent green -composite ../dsg.png bld129.xpm ../wbdsg.png
convert -transparent green -composite ../lsg.png bdd129.xpm ../bblsg.png
convert -transparent green -composite ../dsg.png bdd129.xpm ../bbdsg.png
#King
convert -transparent green -composite ../lsg.png kld129.xpm ../wklsg.png
convert -transparent green -composite ../dsg.png kld129.xpm ../wkdsg.png
convert -transparent green -composite ../lsg.png kdd129.xpm ../bklsg.png
convert -transparent green -composite ../dsg.png kdd129.xpm ../bkdsg.png
#Knight
convert -transparent green -composite ../lsg.png nld129.xpm ../wnlsg.png
convert -transparent green -composite ../dsg.png nld129.xpm ../wndsg.png
convert -transparent green -composite ../lsg.png ndd129.xpm ../bnlsg.png
convert -transparent green -composite ../dsg.png ndd129.xpm ../bndsg.png
#Pawn
convert -transparent green -composite ../lsg.png pld129.xpm ../wplsg.png
convert -transparent green -composite ../dsg.png pld129.xpm ../wpdsg.png
convert -transparent green -composite ../lsg.png pdd129.xpm ../bplsg.png
convert -transparent green -composite ../dsg.png pdd129.xpm ../bpdsg.png
#Queen
convert -transparent green -composite ../lsg.png qld129.xpm ../wqlsg.png
convert -transparent green -composite ../dsg.png qld129.xpm ../wqdsg.png
convert -transparent green -composite ../lsg.png qdd129.xpm ../bqlsg.png
convert -transparent green -composite ../dsg.png qdd129.xpm ../bqdsg.png
#Rook
convert -transparent green -composite ../lsg.png rld129.xpm ../wrlsg.png
convert -transparent green -composite ../dsg.png rld129.xpm ../wrdsg.png
convert -transparent green -composite ../lsg.png rdd129.xpm ../brlsg.png
convert -transparent green -composite ../dsg.png rdd129.xpm ../brdsg.png

#Put pieces on lsg and dsg

#Bishop
convert -transparent green -composite ../lsb.png bld129.xpm ../wblsb.png
convert -transparent green -composite ../dsb.png bld129.xpm ../wbdsb.png
convert -transparent green -composite ../lsb.png bdd129.xpm ../bblsb.png
convert -transparent green -composite ../dsb.png bdd129.xpm ../bbdsb.png
#King
convert -transparent green -composite ../lsb.png kld129.xpm ../wklsb.png
convert -transparent green -composite ../dsb.png kld129.xpm ../wkdsb.png
convert -transparent green -composite ../lsb.png kdd129.xpm ../bklsb.png
convert -transparent green -composite ../dsb.png kdd129.xpm ../bkdsb.png
#Knight
convert -transparent green -composite ../lsb.png nld129.xpm ../wnlsb.png
convert -transparent green -composite ../dsb.png nld129.xpm ../wndsb.png
convert -transparent green -composite ../lsb.png ndd129.xpm ../bnlsb.png
convert -transparent green -composite ../dsb.png ndd129.xpm ../bndsb.png
#Pawn
convert -transparent green -composite ../lsb.png pld129.xpm ../wplsb.png
convert -transparent green -composite ../dsb.png pld129.xpm ../wpdsb.png
convert -transparent green -composite ../lsb.png pdd129.xpm ../bplsb.png
convert -transparent green -composite ../dsb.png pdd129.xpm ../bpdsb.png
#Queen
convert -transparent green -composite ../lsb.png qld129.xpm ../wqlsb.png
convert -transparent green -composite ../dsb.png qld129.xpm ../wqdsb.png
convert -transparent green -composite ../lsb.png qdd129.xpm ../bqlsb.png
convert -transparent green -composite ../dsb.png qdd129.xpm ../bqdsb.png
#Rook
convert -transparent green -composite ../lsb.png rld129.xpm ../wrlsb.png
convert -transparent green -composite ../dsb.png rld129.xpm ../wrdsb.png
convert -transparent green -composite ../lsb.png rdd129.xpm ../brlsb.png
convert -transparent green -composite ../dsb.png rdd129.xpm ../brdsb.png


#Bigger images
convert ../wbls.png -resize +110% ../wbls_big.png
convert ../wbds.png -resize +110% ../wbds_big.png
convert ../bbls.png -resize +110% ../bbls_big.png
convert ../bbds.png -resize +110% ../bbds_big.png
convert ../wkls.png -resize +110% ../wkls_big.png
convert ../wkds.png -resize +110% ../wkds_big.png
convert ../bkls.png -resize +110% ../bkls_big.png
convert ../bkds.png -resize +110% ../bkds_big.png
convert ../wnls.png -resize +110% ../wnls_big.png
convert ../wnds.png -resize +110% ../wnds_big.png
convert ../bnls.png -resize +110% ../bnls_big.png
convert ../bnds.png -resize +110% ../bnds_big.png
convert ../wpls.png -resize +110% ../wpls_big.png
convert ../wpds.png -resize +110% ../wpds_big.png
convert ../bpls.png -resize +110% ../bpls_big.png
convert ../bpds.png -resize +110% ../bpds_big.png
convert ../wqls.png -resize +110% ../wqls_big.png
convert ../wqds.png -resize +110% ../wqds_big.png
convert ../bqls.png -resize +110% ../bqls_big.png
convert ../bqds.png -resize +110% ../bqds_big.png
convert ../wrls.png -resize +110% ../wrls_big.png
convert ../wrds.png -resize +110% ../wrds_big.png
convert ../brls.png -resize +110% ../brls_big.png
convert ../brds.png -resize +110% ../brds_big.png

#Bigger images on red squares
convert ../wblsr.png -resize +110% ../wblsr_big.png
convert ../wbdsr.png -resize +110% ../wbdsr_big.png
convert ../bblsr.png -resize +110% ../bblsr_big.png
convert ../bbdsr.png -resize +110% ../bbdsr_big.png
convert ../wklsr.png -resize +110% ../wklsr_big.png
convert ../wkdsr.png -resize +110% ../wkdsr_big.png
convert ../bklsr.png -resize +110% ../bklsr_big.png
convert ../bkdsr.png -resize +110% ../bkdsr_big.png
convert ../wnlsr.png -resize +110% ../wnlsr_big.png
convert ../wndsr.png -resize +110% ../wndsr_big.png
convert ../bnlsr.png -resize +110% ../bnlsr_big.png
convert ../bndsr.png -resize +110% ../bndsr_big.png
convert ../wplsr.png -resize +110% ../wplsr_big.png
convert ../wpdsr.png -resize +110% ../wpdsr_big.png
convert ../bplsr.png -resize +110% ../bplsr_big.png
convert ../bpdsr.png -resize +110% ../bpdsr_big.png
convert ../wqlsr.png -resize +110% ../wqlsr_big.png
convert ../wqdsr.png -resize +110% ../wqdsr_big.png
convert ../bqlsr.png -resize +110% ../bqlsr_big.png
convert ../bqdsr.png -resize +110% ../bqdsr_big.png
convert ../wrlsr.png -resize +110% ../wrlsr_big.png
convert ../wrdsr.png -resize +110% ../wrdsr_big.png
convert ../brlsr.png -resize +110% ../brlsr_big.png
convert ../brdsr.png -resize +110% ../brdsr_big.png

#Bigger images on green squares
convert ../wblsg.png -resize +110% ../wblsg_big.png
convert ../wbdsg.png -resize +110% ../wbdsg_big.png
convert ../bblsg.png -resize +110% ../bblsg_big.png
convert ../bbdsg.png -resize +110% ../bbdsg_big.png
convert ../wklsg.png -resize +110% ../wklsg_big.png
convert ../wkdsg.png -resize +110% ../wkdsg_big.png
convert ../bklsg.png -resize +110% ../bklsg_big.png
convert ../bkdsg.png -resize +110% ../bkdsg_big.png
convert ../wnlsg.png -resize +110% ../wnlsg_big.png
convert ../wndsg.png -resize +110% ../wndsg_big.png
convert ../bnlsg.png -resize +110% ../bnlsg_big.png
convert ../bndsg.png -resize +110% ../bndsg_big.png
convert ../wplsg.png -resize +110% ../wplsg_big.png
convert ../wpdsg.png -resize +110% ../wpdsg_big.png
convert ../bplsg.png -resize +110% ../bplsg_big.png
convert ../bpdsg.png -resize +110% ../bpdsg_big.png
convert ../wqlsg.png -resize +110% ../wqlsg_big.png
convert ../wqdsg.png -resize +110% ../wqdsg_big.png
convert ../bqlsg.png -resize +110% ../bqlsg_big.png
convert ../bqdsg.png -resize +110% ../bqdsg_big.png
convert ../wrlsg.png -resize +110% ../wrlsg_big.png
convert ../wrdsg.png -resize +110% ../wrdsg_big.png
convert ../brlsg.png -resize +110% ../brlsg_big.png
convert ../brdsg.png -resize +110% ../brdsg_big.png

#Bigger images on blue squares
convert ../wblsb.png -resize +110% ../wblsb_big.png
convert ../wbdsb.png -resize +110% ../wbdsb_big.png
convert ../bblsb.png -resize +110% ../bblsb_big.png
convert ../bbdsb.png -resize +110% ../bbdsb_big.png
convert ../wklsb.png -resize +110% ../wklsb_big.png
convert ../wkdsb.png -resize +110% ../wkdsb_big.png
convert ../bklsb.png -resize +110% ../bklsb_big.png
convert ../bkdsb.png -resize +110% ../bkdsb_big.png
convert ../wnlsb.png -resize +110% ../wnlsb_big.png
convert ../wndsb.png -resize +110% ../wndsb_big.png
convert ../bnlsb.png -resize +110% ../bnlsb_big.png
convert ../bndsb.png -resize +110% ../bndsb_big.png
convert ../wplsb.png -resize +110% ../wplsb_big.png
convert ../wpdsb.png -resize +110% ../wpdsb_big.png
convert ../bplsb.png -resize +110% ../bplsb_big.png
convert ../bpdsb.png -resize +110% ../bpdsb_big.png
convert ../wqlsb.png -resize +110% ../wqlsb_big.png
convert ../wqdsb.png -resize +110% ../wqdsb_big.png
convert ../bqlsb.png -resize +110% ../bqlsb_big.png
convert ../bqdsb.png -resize +110% ../bqdsb_big.png
convert ../wrlsb.png -resize +110% ../wrlsb_big.png
convert ../wrdsb.png -resize +110% ../wrdsb_big.png
convert ../brlsb.png -resize +110% ../brlsb_big.png
convert ../brdsb.png -resize +110% ../brdsb_big.png


#Cropping those bigger images
convert ../wbls_big.png -gravity center -crop 129x129+0+0 +repage ../wbls_big.png
convert ../wbds_big.png -gravity center -crop 129x129+0+0 +repage ../wbds_big.png
convert ../bbls_big.png -gravity center -crop 129x129+0+0 +repage ../bbls_big.png
convert ../bbds_big.png -gravity center -crop 129x129+0+0 +repage ../bbds_big.png
convert ../wkls_big.png -gravity center -crop 129x129+0+0 +repage ../wkls_big.png
convert ../wkds_big.png -gravity center -crop 129x129+0+0 +repage ../wkds_big.png
convert ../bkls_big.png -gravity center -crop 129x129+0+0 +repage ../bkls_big.png
convert ../bkds_big.png -gravity center -crop 129x129+0+0 +repage ../bkds_big.png
convert ../wnls_big.png -gravity center -crop 129x129+0+0 +repage ../wnls_big.png
convert ../wnds_big.png -gravity center -crop 129x129+0+0 +repage ../wnds_big.png
convert ../bnls_big.png -gravity center -crop 129x129+0+0 +repage ../bnls_big.png
convert ../bnds_big.png -gravity center -crop 129x129+0+0 +repage ../bnds_big.png
convert ../wpls_big.png -gravity center -crop 129x129+0+0 +repage ../wpls_big.png
convert ../wpds_big.png -gravity center -crop 129x129+0+0 +repage ../wpds_big.png
convert ../bpls_big.png -gravity center -crop 129x129+0+0 +repage ../bpls_big.png
convert ../bpds_big.png -gravity center -crop 129x129+0+0 +repage ../bpds_big.png
convert ../wqls_big.png -gravity center -crop 129x129+0+0 +repage ../wqls_big.png
convert ../wqds_big.png -gravity center -crop 129x129+0+0 +repage ../wqds_big.png
convert ../bqls_big.png -gravity center -crop 129x129+0+0 +repage ../bqls_big.png
convert ../bqds_big.png -gravity center -crop 129x129+0+0 +repage ../bqds_big.png
convert ../wrls_big.png -gravity center -crop 129x129+0+0 +repage ../wrls_big.png
convert ../wrds_big.png -gravity center -crop 129x129+0+0 +repage ../wrds_big.png
convert ../brls_big.png -gravity center -crop 129x129+0+0 +repage ../brls_big.png
convert ../brds_big.png -gravity center -crop 129x129+0+0 +repage ../brds_big.png

#Cropping those bigger red images
convert ../wblsr_big.png -gravity center -crop 129x129+0+0 +repage ../wblsr_big.png
convert ../wbdsr_big.png -gravity center -crop 129x129+0+0 +repage ../wbdsr_big.png
convert ../bblsr_big.png -gravity center -crop 129x129+0+0 +repage ../bblsr_big.png
convert ../bbdsr_big.png -gravity center -crop 129x129+0+0 +repage ../bbdsr_big.png
convert ../wklsr_big.png -gravity center -crop 129x129+0+0 +repage ../wklsr_big.png
convert ../wkdsr_big.png -gravity center -crop 129x129+0+0 +repage ../wkdsr_big.png
convert ../bklsr_big.png -gravity center -crop 129x129+0+0 +repage ../bklsr_big.png
convert ../bkdsr_big.png -gravity center -crop 129x129+0+0 +repage ../bkdsr_big.png
convert ../wnlsr_big.png -gravity center -crop 129x129+0+0 +repage ../wnlsr_big.png
convert ../wndsr_big.png -gravity center -crop 129x129+0+0 +repage ../wndsr_big.png
convert ../bnlsr_big.png -gravity center -crop 129x129+0+0 +repage ../bnlsr_big.png
convert ../bndsr_big.png -gravity center -crop 129x129+0+0 +repage ../bndsr_big.png
convert ../wplsr_big.png -gravity center -crop 129x129+0+0 +repage ../wplsr_big.png
convert ../wpdsr_big.png -gravity center -crop 129x129+0+0 +repage ../wpdsr_big.png
convert ../bplsr_big.png -gravity center -crop 129x129+0+0 +repage ../bplsr_big.png
convert ../bpdsr_big.png -gravity center -crop 129x129+0+0 +repage ../bpdsr_big.png
convert ../wqlsr_big.png -gravity center -crop 129x129+0+0 +repage ../wqlsr_big.png
convert ../wqdsr_big.png -gravity center -crop 129x129+0+0 +repage ../wqdsr_big.png
convert ../bqlsr_big.png -gravity center -crop 129x129+0+0 +repage ../bqlsr_big.png
convert ../bqdsr_big.png -gravity center -crop 129x129+0+0 +repage ../bqdsr_big.png
convert ../wrlsr_big.png -gravity center -crop 129x129+0+0 +repage ../wrlsr_big.png
convert ../wrdsr_big.png -gravity center -crop 129x129+0+0 +repage ../wrdsr_big.png
convert ../brlsr_big.png -gravity center -crop 129x129+0+0 +repage ../brlsr_big.png
convert ../brdsr_big.png -gravity center -crop 129x129+0+0 +repage ../brdsr_big.png


#Cropping those bigger green images
convert ../wblsg_big.png -gravity center -crop 129x129+0+0 +repage ../wblsg_big.png
convert ../wbdsg_big.png -gravity center -crop 129x129+0+0 +repage ../wbdsg_big.png
convert ../bblsg_big.png -gravity center -crop 129x129+0+0 +repage ../bblsg_big.png
convert ../bbdsg_big.png -gravity center -crop 129x129+0+0 +repage ../bbdsg_big.png
convert ../wklsg_big.png -gravity center -crop 129x129+0+0 +repage ../wklsg_big.png
convert ../wkdsg_big.png -gravity center -crop 129x129+0+0 +repage ../wkdsg_big.png
convert ../bklsg_big.png -gravity center -crop 129x129+0+0 +repage ../bklsg_big.png
convert ../bkdsg_big.png -gravity center -crop 129x129+0+0 +repage ../bkdsg_big.png
convert ../wnlsg_big.png -gravity center -crop 129x129+0+0 +repage ../wnlsg_big.png
convert ../wndsg_big.png -gravity center -crop 129x129+0+0 +repage ../wndsg_big.png
convert ../bnlsg_big.png -gravity center -crop 129x129+0+0 +repage ../bnlsg_big.png
convert ../bndsg_big.png -gravity center -crop 129x129+0+0 +repage ../bndsg_big.png
convert ../wplsg_big.png -gravity center -crop 129x129+0+0 +repage ../wplsg_big.png
convert ../wpdsg_big.png -gravity center -crop 129x129+0+0 +repage ../wpdsg_big.png
convert ../bplsg_big.png -gravity center -crop 129x129+0+0 +repage ../bplsg_big.png
convert ../bpdsg_big.png -gravity center -crop 129x129+0+0 +repage ../bpdsg_big.png
convert ../wqlsg_big.png -gravity center -crop 129x129+0+0 +repage ../wqlsg_big.png
convert ../wqdsg_big.png -gravity center -crop 129x129+0+0 +repage ../wqdsg_big.png
convert ../bqlsg_big.png -gravity center -crop 129x129+0+0 +repage ../bqlsg_big.png
convert ../bqdsg_big.png -gravity center -crop 129x129+0+0 +repage ../bqdsg_big.png
convert ../wrlsg_big.png -gravity center -crop 129x129+0+0 +repage ../wrlsg_big.png
convert ../wrdsg_big.png -gravity center -crop 129x129+0+0 +repage ../wrdsg_big.png
convert ../brlsg_big.png -gravity center -crop 129x129+0+0 +repage ../brlsg_big.png
convert ../brdsg_big.png -gravity center -crop 129x129+0+0 +repage ../brdsg_big.png

#Cropping those bigger blue images
convert ../wblsb_big.png -gravity center -crop 129x129+0+0 +repage ../wblsb_big.png
convert ../wbdsb_big.png -gravity center -crop 129x129+0+0 +repage ../wbdsb_big.png
convert ../bblsb_big.png -gravity center -crop 129x129+0+0 +repage ../bblsb_big.png
convert ../bbdsb_big.png -gravity center -crop 129x129+0+0 +repage ../bbdsb_big.png
convert ../wklsb_big.png -gravity center -crop 129x129+0+0 +repage ../wklsb_big.png
convert ../wkdsb_big.png -gravity center -crop 129x129+0+0 +repage ../wkdsb_big.png
convert ../bklsb_big.png -gravity center -crop 129x129+0+0 +repage ../bklsb_big.png
convert ../bkdsb_big.png -gravity center -crop 129x129+0+0 +repage ../bkdsb_big.png
convert ../wnlsb_big.png -gravity center -crop 129x129+0+0 +repage ../wnlsb_big.png
convert ../wndsb_big.png -gravity center -crop 129x129+0+0 +repage ../wndsb_big.png
convert ../bnlsb_big.png -gravity center -crop 129x129+0+0 +repage ../bnlsb_big.png
convert ../bndsb_big.png -gravity center -crop 129x129+0+0 +repage ../bndsb_big.png
convert ../wplsb_big.png -gravity center -crop 129x129+0+0 +repage ../wplsb_big.png
convert ../wpdsb_big.png -gravity center -crop 129x129+0+0 +repage ../wpdsb_big.png
convert ../bplsb_big.png -gravity center -crop 129x129+0+0 +repage ../bplsb_big.png
convert ../bpdsb_big.png -gravity center -crop 129x129+0+0 +repage ../bpdsb_big.png
convert ../wqlsb_big.png -gravity center -crop 129x129+0+0 +repage ../wqlsb_big.png
convert ../wqdsb_big.png -gravity center -crop 129x129+0+0 +repage ../wqdsb_big.png
convert ../bqlsb_big.png -gravity center -crop 129x129+0+0 +repage ../bqlsb_big.png
convert ../bqdsb_big.png -gravity center -crop 129x129+0+0 +repage ../bqdsb_big.png
convert ../wrlsb_big.png -gravity center -crop 129x129+0+0 +repage ../wrlsb_big.png
convert ../wrdsb_big.png -gravity center -crop 129x129+0+0 +repage ../wrdsb_big.png
convert ../brlsb_big.png -gravity center -crop 129x129+0+0 +repage ../brlsb_big.png
convert ../brdsb_big.png -gravity center -crop 129x129+0+0 +repage ../brdsb_big.png
