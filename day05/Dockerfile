FROM frolvlad/alpine-gxx as BASE
COPY src/aoc.cpp .
RUN g++ aoc.cpp -o /bin/aoc

FROM scratch
COPY --from=BASE /bin/aoc /bin/aoc
COPY input.txt .
ENTRYPOINT ["/bin/aoc"]
