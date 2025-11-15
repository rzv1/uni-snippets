package com.org.example.domain.duck;

import com.org.example.domain.User;
import com.org.example.domain.card.Card;
import lombok.Getter;
import lombok.Setter;

import java.util.List;

@Getter
@Setter
public abstract class Duck extends User {
    private final String type;
    private final Double speed;
    private final Double resistance;
    private final Long cardId;

    public Duck(Long id, String username, String email, String password, String type, Double speed, Double resistance, Long cardId) {
        super(id, username, email, password);
        this.type = type;
        this.speed = speed;
        this.resistance = resistance;
        this.cardId = cardId;
    }

    @Override
    public String toString() {
        return super.toString() + " | " + type + " | " + speed + " | " + resistance;
    }

    @Override
    public String getUserType() {
        return "duck";
    }

    public abstract String getCardType();

    public abstract Card<? extends Duck> getCard(Long id, String name, List<Duck> members);

}
