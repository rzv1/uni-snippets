public class Entity<ID> {
    private ID id;
    public Entity(ID id){
        this.id = id;
    }
    ID getId(){
        return id;
    }
    void setId(ID id){
        this.id = id;
    }
}