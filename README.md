<style>
    img[src*='#center'] { 
        display: block;
        margin: auto;
    }
    .center {
        margin: 0 auto;
        text-align: center;
    } 

    .font-large {
       font-size: 1.2em;
    } 

    .font-small {
        font-size: 0.6em;
    } 

    .font-tiny {
        font-size: 0.3em;
    }

    .font-blue {
        color: lightblue;
    }

    .font-red {
        color: red;
    }


    .font-green {
        color: lightgreen;
    }

    .font-yellow {
        color: yellow;
    }

</style>

<div class="center">
    <h1>
        <div class="font-tiny">
            <p>
                <span class="font-yellow"> u </span>
                <span class="font-green"> W </span>
                <span class="font-yellow"> u </span>
                <span class="font-green"> W </span>
                <span class="font-yellow"> u </span>
                <span class="font-green"> W </span>
                <span class="font-yellow"> u </span>
                <span class="font-green"> W </span>
                <span class="font-yellow"> u </span>
                <span class="font-green"> W </span>
                <span class="font-yellow"> u </span>
            </p> 
            <p class="font-red"> | </p>
            <p class="font-blue"> ^ </p>
        </div>
        <div class="font-large">
            nvaders
        </div>
        <div class="font-small">
            a c++ ncurses game
        </div>
    </h1>
</div>




 - Tested on osx and linux 
 - Requires[ ncurses](https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/)


To build and run
```
cd nvaders
mkdir build && cd build
cmake ..
make
./nvaders
```

Rust clone coming soon...

---

![menu](./nvaders-menu.png#center)
![gameplay](./nvaders-gameplay.png#center)

<div class="center">
Screenshots taken in cool-retro-term
</div>