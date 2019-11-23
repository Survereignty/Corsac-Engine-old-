class Ktoto {
    constructor(name, age) {
        this.name = name
        this.age = age
    }

    get() {
        for (let item in this) {
            console.log(this[item])
        }
    }
}

const Vasa = new Ktoto('vasa', 34)
Vasa.get()
