import math, random

class Player:
    def __init__(self, letter):
        self.letter=letter
    def Move(self, game):
        pass

class ComputerPlayer(Player): # ComputerPlayer Inherits class Player
    def __init__(self, letter):
        super().__init__(letter)
    def Move(self, game):
        square=random.choice(game.availableMoves())
        return square
class HumanPlayer(Player):
    def __init__(self, letter):
        super().__init__(letter)
    def Move(self, game):
        valid_square=False
        val=None
        while not valid_square:
            square=input(self.letter+'\'s turn . Input Move (0-8):')
            try:
                val=int(square)
                if val not in game.availableMoves():
                    raise ValueError
                valid_square= True
            except ValueError:
                print('Invalid square. Try again.')
        return val