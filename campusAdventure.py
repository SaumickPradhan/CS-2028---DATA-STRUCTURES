class Player(object):
    def __init__(self, name, place):
        """Create a player object."""
        self.name = name
        self.place = place
        self.backpack = []
    
    def look(self):
        self.place.look()
        print('Characters in this place:')
        for character in self.place.characters.values():
            print('   ', character.name, '-', character.description)
            if character.belongs:
                print('      Belongs:', ', '.join(character.belongs))

    def talk_to(self, person):
        """Talk to person if person is at player's current place and receive any belongings."""
        if type(person) != str:
            print('Person has to be a string.')
        else:
            character = self.place.characters.get(person)
            if character:
                print(character.name + ' says: ' + character.talk())
                if character.belongs:
                    print(character.name + ' gives you:', ', '.join(character.belongs))
                    for item_name in character.belongs:
                        item = self.place.take(item_name)
                        self.backpack.append(item)
            else:
                print(person + ' is not here.')

    def give(self, item_name, person):
        """Give an item to a character if the character is at player's current place."""
        if type(person) != str:
            print('Person has to be a string.')
        elif type(item_name) != str:
            print('Item name has to be a string.')
        else:
            character = self.place.characters.get(person)
            if character:
                for item in self.backpack:
                    if item.name == item_name:
                        self.backpack.remove(item)
                        character.belongs.append(item_name)
                        print('You give ' + item_name + ' to ' + person + '.')
                        return
                print('You don\'t have ' + item_name + ' in your backpack.')
            else:
                print(person + ' is not here.')

    def use(self, item_name):
        """Use an item from the player's backpack."""
        if type(item_name) != str:
            print('Item name has to be a string.')
        else:
            for item in self.backpack:
                if item.name == item_name:
                    print('You use ' + item_name + '.')
                    # Implement the specific action for each item here, if necessary.
                    return
            print('You don\'t have ' + item_name + ' in your backpack.')



    def check_backpack(self):
        print('In your backpack:')
        if not self.backpack:
            print('    there is nothing.')
        else:
            for item in self.backpack:
                print('   ', item.name, '-', item.description)
        return [item.name for item in self.backpack]


class Character(object):
    def __init__(self, name, description):
        self.name = name
        self.description = description
        self.belongs = []  # A list of items the character has and can give to the player

    def talk(self):
        return self.description

class Thing(object):
    def __init__(self, name, description):
        self.name = name
        self.description = description


class Place(object):
    def __init__(self, name, description, characters, things):
        self.name = name
        self.description = description
        self.characters = {character.name: character for character in characters}
        self.things = {thing.name: thing for thing in things}
        self.exits = {} # {'name': (exit, 'description')}

    def look(self):
        print('You are currently at ' + self.name + '. You take a look around and see:')
        print('Characters:')
        if not self.characters:
            print('    no one in particular')
        else:
            for character in self.characters:
                print('   ', character)
        print('Things:')
        if not self.things:
            print('    nothing in particular')
        else:
            for thing in self.things.values():
                print('   ', thing.name, '-', thing.description)
        self.check_exits()

    def exit_to(self, exit):
        if type(exit) != str:
            print('Exit has to be a string.')
            return self
        elif exit in self.exits:
            print(self.exits[exit][1])
            return self.exits[exit][0]
        else:
            print("Can't go to {} from {}.".format(exit, self.name))
            print("Try looking around to see where to go.")
            return self

    def take(self, thing):
        obj = self.things[thing]
        del self.things[thing]
        return obj

    def check_exits(self):
        print('You can exit to:')
        for exit in self.exits:
            print('   ',exit)

    def add_exits(self, places):
        for place in places:
            self.exits[place.name] = (place, place.description)


# Characters:
randy = Character('Randy', "I can't believe I lost my wallet again! "
                             "I wish someone could find it for me.")
albert = Character('Albert', 'Randy went to DAAP for potluck. You can find her there.')
yulin = Character('Yulin', 'Are you going to potluck? '
                           'You should bring some board games!')
jeffrey = Character('Jeffrey', 'No one brought food to the potluck! '
                               'Maybe the Bearcat Cafe (bcc) is open; we can get food there.')
derrick = Character('Derrick', 'I heard you like board games. '
                               'Have you gone to Gamestop?')
ken = Character('Ken', 'Hey! Want to play ultimate frisbee?')
student = Character('Student', 'I once went into TUC and got lost for 3 days! '
                               'That place is a maze!')


# Things:
wallet = Thing('Wallet', "Looks like Randy's wallet. We should return it to her.")
hotdog = Thing('Hotdog', 'Yummy! Bring it to potluck!')
cards = Thing('Monopoly', 'Just right for potluck!')

# Places:
tuc = Place('Tangeman University Center', 'You are at Tangeman University Center', [], [])
ccm = Place('CCM', 'You are at CCM', [], [wallet])
erc = Place('ERC', 'You are at ERC', [albert], [])
daap = Place('DAAP', 'You are at DAAP', [randy, jeffrey], [])
bcc = Place('Bearcat Cafe', 'You are at Bearcat Cafe', [], [hotdog])
baldwin = Place('Baldwin', 'You are in Baldwin', [yulin], [])
game_store = Place('Gamestop', 'You are at Gamestop', [], [cards])
starbucks = Place('Starbucks', 'You are at Starbucks', [], [])
swift = Place('Swift', 'You are at Swift', [], [])
rhodes = Place('Rhodes Hall', 'You are at Rhodes Hall', [derrick], [])
steger = Place('Steger Center', 'You are at Steger Center', [student], [])
nippert = Place('Nippert Stadium', 'You are at Nippert Stadium', [ken], [])


# Exits:
tuc.add_exits([bcc, rhodes, steger, nippert])
bcc.add_exits([tuc])
rhodes.add_exits([tuc, baldwin])
steger.add_exits([tuc, erc])
nippert.add_exits([tuc, ccm, baldwin, daap])
baldwin.add_exits([nippert, rhodes])
erc.add_exits([ccm, daap, swift, steger])
swift.add_exits([erc, game_store])
ccm.add_exits([erc, nippert])
daap.add_exits([starbucks, erc, nippert])
starbucks.add_exits([daap])
game_store.add_exits([nippert])

# The Player should start at tuc.
me = Player("Saumick", tuc)



try:
    import readline
except ImportError:
    pass



def adv_parse(line):
    tokens = line.split()
    if not tokens:
        raise SyntaxError('No command given')
    command = tokens.pop(0)
    if command in ('talk', 'go'):
        if not tokens or tokens[0] != 'to':
            raise SyntaxError('Did you mean "{}"?'.format(COMMAND_FORMATS[command]))
        return (command + '_to', ' '.join(tokens[1:]))
    elif command == 'check':
        if not tokens or tokens[0] != 'backpack':
            raise SyntaxError('Did you mean "{}"?'.format(COMMAND_FORMATS['check backpack']))
        return ('check_backpack', '')
    else:
        return (command, ' '.join(tokens))


def adv_eval(exp):
    operator, operand = exp[0], exp[1]
    if operator not in COMMAND_NUM_ARGS:
        help()
        raise SyntaxError('Invalid command: {}'.format(operator))
    elif operator in SPECIAL_FORMS:
        function = SPECIAL_FORMS[operator]
    else:
        function = getattr(me, operator)

    if COMMAND_NUM_ARGS[operator] == 0:
        function()
    else:
        function(operand)

def help():
    print('There are {} possible commands:'.format(len(COMMAND_FORMATS)))
    for usage in COMMAND_FORMATS.values():
        print('   ', usage)

def check_win_state(player):
    """Checks if the player is in a winning state."""
    if player.place != starbucks:
        return False

    print()
    if len(player.check_backpack()) != 3:
        print()
        print("Looks like you're missing some items. Can't go to the potluck yet!")
        return False
    return True


def read_eval_print_loop():
    print(WELCOME_MESSAGE)
    if not isinstance(me, Player):
        print('Oh no! You need to create a player in lab07.py to start the game.')
        return

    help()
    while True:
        if check_win_state(me):
            print(WIN_MESSAGE)
            return
        print()
        try:
            line = input('adventure> ')
            exp = adv_parse(line)
            adv_eval(exp)
        except (KeyboardInterrupt, EOFError, SystemExit): # If you ctrl-c or ctrl-d
            print('\nGood game. Bye!')
            return
        # If the player input was badly formed or if something doesn't exist
        except SyntaxError as e:
            print('ERROR:', e)


COMMAND_FORMATS = {
    'look': 'look',
    'go': 'go to [direction]',
    'take': 'take [thing]',
    'talk': 'talk to [character]',
    'check backpack': 'check backpack',
    'help': 'help',
}

COMMAND_NUM_ARGS = {
    'look': 0,
    'go_to': 1,
    'take': 1,
    'talk_to': 1,
    'check_backpack': 0,
    'help': 0,
}

SPECIAL_FORMS = {
    'help': help,
}

WELCOME_MESSAGE = """
Welcome to the adventure game!

It's a bright sunny day.
You are a cute little squirrel named {},
wandering around UC campus looking for food.

Let's go to ccm (CCM Cafe)
and see what we can find there!
""".format(me.name if isinstance(me, Player) else '______')

WIN_MESSAGE = """
You arrived just in time for the potluck!

Randy thanks you for finding her wallet.
Jeffrey devours the hot dog you brought.
Everyone gathers around for a long game of Monopoly.

Congratulations! You won the adventure game!
"""
if __name__ == '__main__':
  read_eval_print_loop()
  
# import doctest
# if __name__ == "__main__":
#     doctest.testmod(verbose=True)
