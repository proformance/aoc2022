import 'package:test/test.dart';
import '../aoc.dart';

void main() {
  final input = '''2-4,6-8
2-3,4-5
5-7,7-9
2-8,3-7
6-6,4-6
2-6,4-8''';

  final assignments =
      input.split('\n').map((line) => ElfAssignment.parse(line)).toList();

  group('basic tests', () {
    test('part1', () {
      expect(solutionPart1(assignments), equals(2));
    });
    test('part2', () {
      expect(solutionPart2(assignments), equals(4));
    });
  });
}
