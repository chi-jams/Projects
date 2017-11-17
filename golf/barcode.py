#82c
#https://codegolf.stackexchange.com/questions/148181/is-my-barcode-valid
fn = lambda n: (sum([d*(3 if i%2==0 else 1)for i,d in enumerate(n[:-1])])+n[-1])%10==0
