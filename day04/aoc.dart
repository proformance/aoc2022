import 'dart:io';
import 'dart:convert';
import 'dart:async';

int solutionPart1(List<ElfAssignment> assignments) {
  return assignments
      .where((assignment) => (assignment.elf1AssigmentRange
              .containsRange(assignment.elf2AssigmentRange) ||
          assignment.elf1AssigmentRange
              .isContainedBy(assignment.elf2AssigmentRange)))
      .length;
}

int solutionPart2(List<ElfAssignment> assignments) {
  return assignments
      .where((assignment) => (assignment.elf1AssigmentRange
          .overlapsWith(assignment.elf2AssigmentRange)))
      .length;
}

void main() async {
  print('Dart');
  List<ElfAssignment> input = await parseInputToElfAssignments("input.txt");
  String part = Platform.environment["part"] ?? "part1";
  if (part == "part1") {
    print(solutionPart1(input));
  } else if (part == "part2") {
    print(solutionPart2(input));
  } else {
    print("Unknown part " + part);
  }
}

Future<List<ElfAssignment>> parseInputToElfAssignments(String path) async {
  return new File(path)
      .openRead()
      .transform(utf8.decoder)
      .transform(const LineSplitter())
      .map((line) => ElfAssignment.parse(line))
      .toList();
}

class Range {
  final int start;
  final int stop;
  Range({required this.start, required this.stop});

  bool isContainedBy(Range otherRange) =>
      (this.start >= otherRange.start && this.stop <= otherRange.stop);

  bool containsRange(Range otherRange) =>
      (this.start <= otherRange.start && this.stop >= otherRange.stop);

  bool overlapsWith(Range otherRange) =>
      (this.start <= otherRange.stop && this.stop >= otherRange.start) ||
      (this.start >= otherRange.stop && this.stop <= otherRange.start);
}

class ElfAssignment {
  final Range elf1AssigmentRange;
  final Range elf2AssigmentRange;

  ElfAssignment({
    required this.elf1AssigmentRange,
    required this.elf2AssigmentRange,
  });

  factory ElfAssignment.parse(String line) {
    List<String> assignments = line.split(',');
    final elf1 = assignments[0].split('-').map((e) => int.parse(e)).toList();
    final elf2 = assignments[1].split('-').map((e) => int.parse(e)).toList();
    return ElfAssignment(
      elf1AssigmentRange: Range(start: elf1[0], stop: elf1[1]),
      elf2AssigmentRange: Range(start: elf2[0], stop: elf2[1]),
    );
  }
}
