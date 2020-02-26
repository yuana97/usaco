# http://www.usaco.org/index.php?page=viewproblem2&cpid=987
# Question:
# N space separated words, lines must be <= K characers.
# Print out the formatted essay.

# Input: N, K followed by unformatted essay

# Solution (python):
# Code the instructions: add letters until char limit K is exceeded at which
# point you start a new line

# open word.in in read mode and call the input stream fin
with open("word.in", "r") as fin:
    # put each line of the file into a list L
    L = list(fin)
    # split first line into N, K chars, cast them into integers, assign to N, K vars.
    N, K = map(int, L[0].split())
    # open word.out in write mode as fout
    with open("word.out", "w") as fout:
        w = 0  # w = current line length
        # split letters into array of words, go thru each word c
        for c in L[1].split():  # go through each word
            # line too long => write on new line, update w=linelength
            if w+len(c) > K:  # place on new line
                fout.write("\n"+c)
                w = len(c)
            # else add to current line
            else:
                # add w>0 check here so we don't add space at start of line
                if w > 0:
                    fout.write(" ")
                # write c to line and update w=linelength
                fout.write(c)
                w += len(c)
        # after writing essay, print newline
        fout.write("\n")
