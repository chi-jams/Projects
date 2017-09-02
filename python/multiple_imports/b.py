#pylint: disable-all

class b:
    def __init__(self, number):
        self.cool_var = number

    def change_cool_var(self):
        self.cool_var -= 2

    def show_cool_var(self):
        print(self.cool_var)