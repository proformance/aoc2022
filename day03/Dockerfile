FROM gcc as BASE
COPY src/aoc.cpp .
RUN gcc aoc.cpp -o /bin/aoc -static -lstdc++ -std=c++11

FROM scratch
COPY --from=BASE /bin/aoc /bin/
COPY input.txt .
ENTRYPOINT ["/bin/aoc"]
