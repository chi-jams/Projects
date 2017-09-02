# https://codegolf.stackexchange.com/questions/129267/print-the-stackexchange-favicon
def v1():
    # uncompressed
    d = '-'*21
    s = ' '*19
    m = d + '\n|' + s + '|'
    b = ' ' * 11 + '|'

    o = '\n'.join([' ' + '_' * 19, 
                   '/' + s + '\\', 
                   m, m, d,
                   '\\' + '_'*10 + ' ' * 4 + '_'*5 + '/',
                   b + ' ' * 2 + '/',
                   b + ' /',
                   b + '/'])
    return o

def v2():
    d='-'*21
    s=' '*19
    m=d+'\n|'+s+'|'
    b=' '*11+'|'
    o='\n'.join([' '+'_'*19,'/'+s+'\\',m,m,d,'\\'+'_'*10+' '*4+'_'*5+'/',b+' '*2+'/',b+' /',b+'/'])
    return o

def v3():
    d,s,U,b,f,n,l='- _\\/\n|'
    D=d*21
    S=s*19
    m=D+n+l+S+l
    B=s*11+l
    o=n.join([s+U*19,f+S+b,m,m,D,b+U*10+s*4+U*5+f,B+s*2+f,B+s+f,B+f])
    return o

d,s,U,b,f,n,l='- _\\/\n|'
D=d*21
S=s*19
m=D+n+l+S+l
B=s*11+l
print(s+U*19,f+S+b,m,m,D,b+U*10+s*4+U*5+f,B+s*2+f,B+s+f,B+f,sep=n)

a=""" ___________________
/                   \\
---------------------
|                   |
---------------------
|                   |
---------------------
\__________    _____/
           |  /
           | /
           |/"""
print(a)