package io.muic.ooc.webapp.config;

import lombok.Builder; // In the tutorial ajarn replace Lombok with normal Getter/Setter but since it kinda works here I'll keep Lombok
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
@Builder
public class ConfigProperties {

    private String databaseDriverClassName;
    private String databaseConnectionUrl;
    private String databaseUsername;
    private String databasePassword;


}
