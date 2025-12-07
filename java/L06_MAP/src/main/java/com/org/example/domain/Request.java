package com.org.example.domain;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class Request extends Entity<Long> {
    private Long fromId;
    private Long toId;
    private RequestType status;

    public Request(Long fromId, Long toId, RequestType status) {
        this.fromId = fromId;
        this.toId = toId;
        this.status = status;
    }
}
