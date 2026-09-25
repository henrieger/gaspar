FROM gcc:15.2.0 AS builder
USER root

WORKDIR /build

ARG VERSION=26.09

COPY gaspar-${VERSION}.tar.gz .
RUN tar -xf gaspar-${VERSION}.tar.gz

WORKDIR /build/gaspar-${VERSION}
RUN ./configure && make && make install

RUN ldd /usr/local/bin/gaspar

FROM scratch AS final
WORKDIR /

COPY --from=builder /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=builder /usr/lib/x86_64-linux-gnu/libc.so.6 /usr/lib/x86_64-linux-gnu/libc.so.6
COPY --from=builder /usr/lib/x86_64-linux-gnu/libm.so.6 /usr/lib/x86_64-linux-gnu/libm.so.6
COPY --from=builder /usr/local/bin/gaspar /usr/bin/gaspar
COPY --from=builder /usr/local/lib/libgaspar.* /usr/lib
COPY --from=builder /usr/local/include/gaspar/* /usr/include/gaspar

CMD [ "/usr/bin/gaspar" ]
