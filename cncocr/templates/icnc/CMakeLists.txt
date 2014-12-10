# to be included from $CNCROOT/samples/CMakeLists.txt

set(myname {{g.name}})

add_executable(${myname} ${myname}_main.cpp {% for stepfun in g.finalAndSteps -%} {{"${myname}_" ~ stepfun.collName ~ ".cpp " if not loop.first}} {%- endfor %})
target_link_libraries(${myname} ${NEEDED_LIBS})

if(USE_ITAC)
  set_itac_link_flags(${myname})
endif(USE_ITAC)

unset(myname CACHE)
