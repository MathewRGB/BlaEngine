#include "gtest/gtest.h"
#include "helper_for_tests.h"
#include "source/calculation/game_state_controller.h"
#include "source/calculation/move_generator.h"

using namespace blaengine::calculation;

TEST(BishopMoves, test_general_moves_pos35) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 35;
  game_state.board.fields[field_before] = Piece::white_bishop;
  vector<ushort> possible_fields = {44, 53, 62, 26, 17, 8, 28,
                                    21, 14, 7,  42, 49, 56};

  auto knight_moves = move_generator.getBishopMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(BishopMoves, test_no_move_possible) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 18;
  game_state.board.fields[field_before] = Piece::white_bishop;
  game_state.board.fields[25] = Piece::white_king;
  game_state.board.fields[27] = Piece::white_pawn;
  game_state.board.fields[9] = Piece::white_queen;
  game_state.board.fields[11] = Piece::white_rook;

  auto knight_moves = move_generator.getBishopMoves(game_state, field_before);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, {}));
}

TEST(BishopMoves, test_general_moves_pos56) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 56;
  game_state.board.fields[field_before] = Piece::black_bishop;
  game_state.board.fields[42] = Piece::white_pawn;
  game_state.board.fields[21] = Piece::black_knight;
  vector<ushort> possible_fields = {49, 42};

  auto knight_moves = move_generator.getBishopMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(BishopMoves, test_general_moves_pos37) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 37;
  game_state.board.fields[field_before] = Piece::black_bishop;
  game_state.board.fields[19] = Piece::white_pawn;
  game_state.board.fields[46] = Piece::black_knight;
  vector<ushort> possible_fields = {30, 23, 44, 51, 58, 28, 19};

  auto knight_moves = move_generator.getBishopMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(BishopMoves, test_general_moves_pos55) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 55;
  game_state.board.fields[field_before] = Piece::white_bishop;
  game_state.board.fields[37] = Piece::black_queen;
  game_state.board.fields[62] = Piece::white_rook;
  vector<ushort> possible_fields = {46, 37};

  auto knight_moves = move_generator.getBishopMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}

TEST(BishopMoves, test_general_moves_pos14) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 14;
  game_state.board.fields[field_before] = Piece::black_bishop;
  game_state.board.fields[35] = Piece::black_knight;
  game_state.board.fields[5] = Piece::white_knight;
  vector<ushort> possible_fields = {7, 21, 28, 5, 23};

  auto knight_moves = move_generator.getBishopMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}
