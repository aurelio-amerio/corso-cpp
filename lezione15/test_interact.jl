using Markdown
using Pkg


using Blink
# Blink.AtomShell.install()

using Interact
#%%
text = @md_str """# Title
    This is a markdown test
    ## Subsection
    and this is a subsection
    """
text2=display(text)
loadbutton = filepicker()
hellobutton = button("Hello!")
goodbyebutton = button("Good bye!")

ui = vbox( # put things one on top of the other
    loadbutton,
    hbox( # put things one next to the other
        pad(1em, hellobutton), # to allow some white space around the widget
        pad(1em, goodbyebutton),
    ),
    text
)
display(ui)
#%%
w = Window()
body!(w, ui);
